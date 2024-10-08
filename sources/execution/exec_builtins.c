/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 20:02:12 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"
#include "minishell.h"

static int	copy_stdout(t_core *core_data)
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

static int	fork_bt(t_core *core, t_ast *node, char **args)
{
	pid_t	pid;
	int		error;

	pid = fork();
	if (pid == FAILURE)
	{
		ft_rm_split(args);
		perror_switch(core->errors, "kikishell", NULL);
		return (FAILURE);
	}
	node->data->pid = pid;
	if (pid == 0)
	{
		if (pre_process_exec(core, node) == FAILURE)
		{
			clean_child(core, args);
			exit(1);
		}
		error = chr_exec_bt((const char **)args, &(core->env), core);
		close_all_pipes(core);
		clean_child(core, args);
		exit(error);
	}
	clean_parent(core, node, args);
	return (SUCCESS);
}

int	process_built_in(t_core *core, t_ast *node, char **args)
{
	int		error;
	int		save_fd;

	if (node->data->index != -1)
	{
		return (fork_bt(core, node, args));
	}
	save_fd = -1;
	if (ft_strncmp(args[0], "exit", 5) != 0)
		save_fd = copy_stdout(core);
	if (pre_process_exec(core, node) == FAILURE)
	{
		node->data->exit_code = 1;
		restore_stdout(core->errors, save_fd);
		return (FAILURE);
	}
	error = chr_exec_bt((const char **)args, &(core->env), core);
	node->data->require_wait = false;
	node->data->exit_code = error;
	if (node->data->index > 0)
		close_pipe(core);
	restore_stdout(core->errors, save_fd);
	ft_rm_split(args);
	return (SUCCESS);
}
