/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 17:12:00 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

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

void	clear_ats(t_ats *ats, int flag)
{
	if (flag & ATS_ROOT)
		clear_tree(ats->root);
	if (flag & ATS_PROMPT)
		free(ats->prompt);
	if (flag & ATS_REDIR)
		ft_clear_queue(ats->queue_redir, &clear_redir_queue);
	if (flag & ATS_HEREDOC)
		ft_clear_queue(ats->queue_heredoc, &clear_heredoc_queue);
	if (flag & ATS_ENV)
		ft_lstclear(&(ats->env), &free);
}
