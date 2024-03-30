/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 15:29:14 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

int	open_redirs_pipe(t_queue *redir, t_queue *heredoc, t_ats *root)
{
	if (!root)
		return (SUCCESS);
	open_redirs_pipe(redir, heredoc, root->left);
	return (open_redir(redir, heredoc, root));
}

int	open_redir(t_queue *redir, t_queue *heredoc, const t_ats *root)
{
	t_queue_redir	*node;
	int				exit_code;
	int				index;

	index = root->data->nb_redir;
	exit_code = SUCCESS;
	while (index > 0 && exit_code == SUCCESS)
	{
		node = (t_queue_redir *)ft_dequeue(redir);
		if (!node)
		{
			return (FAILURE);
		}
		if (node->type_redir == REDIR_IN)
			exit_code = open_redir_in(node);
		else if (node->type_redir == REDIR_OUT)
			exit_code = open_redir_out(node);
		else if (node->type_redir == REDIR_OUT_APPEND)
			exit_code = open_redir_append(node);
		else if (node->type_redir == REDIR_HEREDOC)
			exit_code = open_redir_heredoc(heredoc);
		index--;
	}
	return (exit_code);
}
