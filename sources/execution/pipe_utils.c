/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:16:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:43:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "parser.h"

static int	dup_in(t_queue_pipe *data)
{
	if (close(data->pipe_fd[WRITE]) == FAILURE)
	{
		perror("close in write");
		return (FAILURE);
	}
	if (dup2(data->pipe_fd[READ], STDIN_FILENO) == FAILURE)
	{
		perror("dup2");
		close(data->pipe_fd[READ]);
		return (FAILURE);
	}
	if (close(data->pipe_fd[READ]) == FAILURE)
	{
		perror("close in read");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	dup_out(t_queue_pipe *data)
{
	if (close(data->pipe_fd[READ])== FAILURE)
	{
		perror("close out read");
		return (FAILURE);
	}
	if (dup2(data->pipe_fd[WRITE], STDOUT_FILENO) == FAILURE)
	{
		perror("dup2");
		close(data->pipe_fd[WRITE]);
		return (FAILURE);
	}
	if (close(data->pipe_fd[WRITE]) == FAILURE)
	{
		perror("close out write");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	dup_pipe(t_maindata *core_data, int index)
{
	t_queue_pipe	*data;

	data = NULL;
	if (index - 1 >= 0)
	{
		data = ft_dequeue(core_data->queue_pipe);
		if (dup_in(data) == FAILURE)
		{
			free(data);
			return (FAILURE);
		}
	}
	free(data);
	data = ft_dequeue(core_data->queue_pipe);
	if (index != (int)count_nodes(core_data->root, 0) - 1)
	{
		if (dup_out(data) == FAILURE)
		{
			free(data);
			return (FAILURE);
		}
	}
	free(data);
	return (SUCCESS);
}

int	close_pipe(t_maindata *core_data)
{
	t_queue_pipe	*data;

	data = ft_dequeue(core_data->queue_pipe);
	if (data == NULL)
		return (FAILURE);
	if (close(data->pipe_fd[READ]) == FAILURE)
	{
		free(data);
		return (FAILURE);
	}
	if (close(data->pipe_fd[WRITE]) == FAILURE)
	{
		free(data);
		return (FAILURE);
	}
	free(data);
	return (SUCCESS);
}

void	close_all_pipes(t_maindata *core_data)
{
	t_queue_pipe	*data;

	while (true)
	{
		data = ft_dequeue(core_data->queue_pipe);
		if (data == NULL)
			break ;
		if (close(data->pipe_fd[READ]) == FAILURE)
		{
			perror_switch(core_data->errors, "close", NULL);
			free(data);
			return ;
		}
		if (close(data->pipe_fd[WRITE]) == FAILURE)
		{
			perror_switch(core_data->errors, "close", NULL);
			free(data);
			return ;
		}
		free(data);
	}
	return ;
}
