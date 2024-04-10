/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:42:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

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

void	process_built_in(t_maindata *core_data, t_ats *node, char **args)
{
	pid_t	pid;
	int		error;
	int		save_fd;

	if (node->data->index != -1)
	{
		pid = fork();
		if (pid == FAILURE)
		{
			errno = EIO;
			perror_switch(core_data->errors, "fork", NULL);
			return ;
		}
		node->data->pid = pid;
		if (pid == 0)
		{
			if (core_data->history_fd != -1)
				close(core_data->history_fd);
			if (core_data->stdin_fd != -1)
				close(core_data->stdin_fd);
			if (pre_process_exec(core_data, node) == FAILURE)
			{
				ft_rm_split(args);
				clear_ats(core_data, CORE_ALL);
				exit(1);
			}
			error = chr_exec_bt((const char **)args, &(core_data->env),
					core_data);
			close_all_pipes(core_data);
			ft_rm_split(args);
			clear_ats(core_data, CORE_ALL);
			exit(error);
		}
		clean_parent(core_data, node);
		return ;
	}
	save_fd = -1;
	if (ft_strncmp(args[0], "exit", 5) != 0)
		save_fd = copy_stdout(core_data);
	if (pre_process_exec(core_data, node) == FAILURE)
	{
		node->data->exit_code = 1;
		restore_stdout(core_data->errors, save_fd);
		return ;
	}
	node->data->require_wait = false;
	error = chr_exec_bt((const char **)args, &(core_data->env),
			core_data);
	node->data->exit_code = error;
	if (node->data->index > 0)
		close_pipe(core_data);
	restore_stdout(core_data->errors, save_fd);
}
