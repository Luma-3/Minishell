/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 16:45:35 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"
#include "minishell.h"

static int	copy_stdout(t_maindata *core_data)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == FAILURE)
	{
		errno = EIO;
		perror_switch(core_data->errors, "dup", NULL);
		return (FAILURE);
	}
	return (fd);
}

static void	restore_stdout(t_error *errors, int save_fd)
{
	if (save_fd == -1)
		return ;
	if (dup2(save_fd, STDOUT_FILENO) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "dup2", NULL);
	}
	if (close(save_fd) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "close", NULL);
	}
}

static int	fork_bt(t_maindata *core, t_ast *node, char **args)
{
	pid_t	pid;
	int		error;

	pid = fork();
	if (pid == FAILURE)
	{
		perror_switch(core->errors, "fork", NULL);
		return (FAILURE);
	}
	node->data->pid = pid;
	if (pid == 0)
	{
		if (pre_process_exec(core, node) == FAILURE)
		{
			ft_rm_split(args);
			clear_ats(core, CORE_ALL);
			exit(1);
		}
		error = chr_exec_bt((const char **)args, &(core->env), core);
		(close_all_pipes(core), ft_rm_split(args));
		clear_ats(core, CORE_ALL);
		exit(error);
	}
	clean_parent(core, node);
	return (SUCCESS);
}

void	process_built_in(t_maindata *core, t_ast *node, char **args)
{
	int		error;
	int		save_fd;

	if (node->data->index != -1)
	{
		fork_bt(core, node, args);
		return ;
	}
	save_fd = -1;
	if (ft_strncmp(args[0], "exit", 5) != 0)
		save_fd = copy_stdout(core);
	if (pre_process_exec(core, node) == FAILURE)
	{
		node->data->exit_code = 1;
		restore_stdout(core->errors, save_fd);
		return ;
	}
	error = chr_exec_bt((const char **)args, &(core->env), core);
	node->data->require_wait = false;
	node->data->exit_code = error;
	if (node->data->index > 0)
		close_pipe(core);
	restore_stdout(core->errors, save_fd);
}
