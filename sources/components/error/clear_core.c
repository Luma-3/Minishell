/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 18:38:49 by jbrousse         ###   ########.fr       */
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

static void	clear_else(t_maindata *ats, int flag)
{
	if (flag & CORE_PIPE && ats->queue_pipe != NULL)
	{
		ft_clear_queue(ats->queue_pipe, &clear_pipe_queue);
		ats->queue_pipe = NULL;
	}
	if (flag & CORE_ENV && ats->env != NULL)
	{
		ft_lstclear(&(ats->env), &free);
		ats->env = NULL;
	}
	if (flag & CORE_UNAME && ats->uname != NULL)
	{
		free(ats->uname);
		ats->uname = NULL;
	}
	if (flag & CORE_PATH && ats->path != NULL)
	{
		free(ats->path);
		ats->path = NULL;
	}
}

void	clear_ats(t_maindata *ats, int flag)
{
	if (flag & CORE_ROOT && ats->root != NULL)
	{
		clear_tree(ats->root, &free_data_tree);
		ats->root = NULL;
	}
	if (flag & CORE_PROMPT && ats->prompt != NULL)
	{
		free(ats->prompt);
		ats->prompt = NULL;
	}
	if (flag & CORE_REDIR && ats->queue_redir != NULL)
	{
		ft_clear_queue(ats->queue_redir, &clear_redir_queue);
		ats->queue_redir = NULL;
	}
	if (flag & CORE_HEREDOC && ats->queue_heredoc != NULL)
	{
		ft_clear_queue(ats->queue_heredoc, &clear_heredoc_queue);
		ats->queue_heredoc = NULL;
	}
	clear_else(ats, flag);
}
