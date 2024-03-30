/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 16:08:14 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "parser.h"

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

int	dup_pipe(t_maindata *core_data, int index)
{
	t_queue_pipe	*data;

	data = NULL;
	if (index - 1 >= 0)
	{
		data = ft_dequeue(core_data->queue_pipe);
		if (dup_in(data) == FAILURE)
			return (FAILURE);
	}
	data = ft_peek(core_data->queue_pipe);
	if (index != (int)count_nodes(core_data->root, 0) - 1)
	{
		if (dup_out(data) == FAILURE)
			return (FAILURE);
	}
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

int	handle_pipeline(t_maindata *core_data, const t_ats *node)
{
	t_queue		*tmp_redir;
	t_queue		*tmp_heredoc;

	if (node->data->index != 0)
	{
		return (SUCCESS);
	}
	tmp_redir = ft_dup_queue(core_data->queue_redir);
	tmp_heredoc = ft_dup_queue(core_data->queue_heredoc);
	if (!tmp_redir || !tmp_heredoc)
		return (FAILURE);
	return (open_redirs_pipe(core_data, core_data->root));
}
