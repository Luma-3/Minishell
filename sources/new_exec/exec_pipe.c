/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 14:49:22 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "redirection.h"
#include "ms_builtins.h"
#include <stdio.h>

static int	dup_in(t_queue_pipe *data)
{
	close(data->pipe_fd[WRITE]);
	if (dup2(data->pipe_fd[READ], STDIN_FILENO) == FAILURE)
	{
		close(data->pipe_fd[READ]);
		return (FAILURE);
	}
	close(data->pipe_fd[READ]);
	return (SUCCESS);
}

static int	dup_out(t_queue_pipe *data)
{
	close(data->pipe_fd[READ]);
	if (dup2(data->pipe_fd[WRITE], STDOUT_FILENO) == FAILURE)
	{
		close(data->pipe_fd[WRITE]);
		return (FAILURE);
	}
	close(data->pipe_fd[WRITE]);
	return (SUCCESS);
}


int	dup_pipe(t_ats *ats, int index)
{
	t_queue_pipe	*data;

	data = NULL;
	if (index - 1 >= 0)
	{
		data = ft_dequeue(ats->queue_pipe);
		if (dup_in(data) == FAILURE)
			return (FAILURE);
	}
	data = ft_peek(ats->queue_pipe);
	if (index != (int)count_nodes(ats->root, 0) - 1)
	{
		if (dup_out(data) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
