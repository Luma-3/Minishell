/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 17:55:23 by anthony          ###   ########.fr       */
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
		perror_switch(core_data->errors, "dup");
		return (FAILURE);
	}
	return (fd);
}

static void	restore_stdout(t_error *errors, int save_fd)
{
	if (dup2(save_fd, STDOUT_FILENO) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "dup2");
	}
	if (close(save_fd) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "close");
	}
}

void	process_built_in(t_maindata *core_data, t_ats *node, char **args)
{
	pid_t	pid;
	int		error;
	int		save_fd;

	save_fd = copy_stdout(core_data);
	if (node->data->index != -1)
	{
		pid = fork();
		if (pid == FAILURE)
		{
			errno = EIO;
			perror_switch(core_data->errors, "fork");
			return ;
		}
		node->data->pid = pid;
		if (pid == 0)
		{
			if (pre_process_exec(core_data, node) == FAILURE)
			{
				node->data->exit_code = 1;
				exit(1);
			}
			error = exec_builtin((const char **)args, &(core_data->env),
					core_data->errors);
			close_all_pipes(core_data);
			close(core_data->history_fd);
			close(core_data->stdin_fd);
			node->data->exit_code = error;
			exit(error);
		}
		restore_stdout(core_data->errors, save_fd);
		clean_parent(core_data, node);
		return ;
	}
	if (pre_process_exec(core_data, node) == FAILURE)
	{
		node->data->exit_code = 1;
		restore_stdout(core_data->errors, save_fd);
		return ;
	}
	node->data->require_wait = false;
	error = exec_builtin((const char **)args, &(core_data->env),
			core_data->errors);
	node->data->exit_code = error;
	if (node->data->index > 0)
		close_pipe(core_data);
	restore_stdout(core_data->errors, save_fd);
}
