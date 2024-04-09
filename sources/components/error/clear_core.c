/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 12:29:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "core_data.h"
#include "parser.h"

static void	clear_heredoc_queue(void *content)
{
	t_queue_heredoc	*heredoc;

	heredoc = (t_queue_heredoc *)content;
	if (access(heredoc->file_name, F_OK) == 0)
		unlink(heredoc->file_name);
	free(heredoc->file_name);
	free(heredoc->delimiter);
	free(heredoc);
}

static void	clear_redir_queue(void *content)
{
	t_queue_redir	*redir;

	redir = (t_queue_redir *)content;
	free(redir->file_name);
	free(redir);
}

static void	clear_pipe_queue(void *content)
{
	t_queue_pipe	*pipe;

	pipe = (t_queue_pipe *)content;
	free(pipe);
}

static void	clear_else(t_maindata *core_data, int flag)
{
	if (flag & CORE_PIPE && core_data->queue_pipe != NULL)
	{
		ft_clear_queue(core_data->queue_pipe, &clear_pipe_queue);
		core_data->queue_pipe = NULL;
	}
	if (flag & CORE_ENV && core_data->env != NULL)
	{
		ft_lstclear(&(core_data->env), &free);
		core_data->env = NULL;
	}
	if (flag & CORE_UNAME && core_data->uname != NULL)
	{
		free(core_data->uname);
		core_data->uname = NULL;
	}
	if (flag & CORE_PATH && core_data->path != NULL)
	{
		free(core_data->path);
		core_data->path = NULL;
	}
	if (flag & CORE_HISTORY && core_data->history_fd != -1)
	{
		close(core_data->history_fd);
		core_data->history_fd = -1;
	}
}

void	clear_ats(t_maindata *core_data, int flag)
{
	if (flag & CORE_ROOT && core_data->root != NULL)
	{
		clear_tree(core_data->root, &free_data_tree);
		core_data->root = NULL;
	}
	if (flag & CORE_PROMPT && core_data->prompt != NULL)
	{
		free(core_data->prompt);
		core_data->prompt = NULL;
	}
	if (flag & CORE_REDIR && core_data->queue_redir != NULL)
	{
		ft_clear_queue(core_data->queue_redir, &clear_redir_queue);
		core_data->queue_redir = NULL;
	}
	if (flag & CORE_HEREDOC && core_data->queue_heredoc != NULL)
	{
		ft_clear_queue(core_data->queue_heredoc, &clear_heredoc_queue);
		core_data->queue_heredoc = NULL;
	}
	if (flag & CORE_STDIN && core_data->stdin_fd != -1)
	{
		(close(core_data->stdin_fd), core_data->stdin_fd = -1);
	}
	clear_else(core_data, flag);
}
