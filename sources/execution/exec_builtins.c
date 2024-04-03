/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/03 17:59:54 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"

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
	int		error;
	int		save_fd;

	save_fd = copy_stdout(core_data);
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
	restore_stdout(core_data->errors, save_fd);
}
