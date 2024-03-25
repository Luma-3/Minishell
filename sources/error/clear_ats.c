/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 11:00:16 by jbrousse         ###   ########.fr       */
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

static void	free_data_tree(void *content)
{
	t_token	*data;

	data = (t_token *)content;
	if (data->cmd != NULL)
		free(data->cmd);
	if (data->argv != NULL)
		ft_rm_split(data->argv);
	free(data);
}

void	clear_ats(t_ats *ats, int flag)
{
	if (flag & ATS_ROOT && ats->root != NULL)
	{
		clear_tree(ats->root, &free_data_tree);
		ats->root = NULL;
	}
	if (flag & ATS_PROMPT && ats->prompt != NULL)
	{
		free(ats->prompt);
		ats->prompt = NULL;
	}
	if (flag & ATS_REDIR && ats->queue_redir != NULL)
	{
		ft_clear_queue(ats->queue_redir, &clear_redir_queue);
		ats->queue_redir = NULL;
	}
	if (flag & ATS_HEREDOC && ats->queue_heredoc != NULL)
	{
		ft_clear_queue(ats->queue_heredoc, &clear_heredoc_queue);
		ats->queue_heredoc = NULL;
	}
	if (flag & ATS_PIPE && ats->queue_pipe != NULL)
	{
		ft_clear_queue(ats->queue_pipe, &clear_pipe_queue);
		ats->queue_pipe = NULL;
	}
	if (flag & ATS_ENV && ats->env != NULL)
	{
		ft_lstclear(&(ats->env), &free);
		ats->env = NULL;
	}
}
