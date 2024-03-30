/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 16:15:49 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

int	open_redirs_pipe(t_maindata *core_data, t_ats *root)
{
	if (!root)
		return (SUCCESS);
	open_redirs_pipe(core_data, root->left);
	return (open_redir(core_data, root));
}

static int	open_redir_type(t_queue_redir *node, t_queue *heredoc)
{
	if (node->type_redir == REDIR_IN)
		return (open_redir_in(node));
	if (node->type_redir == REDIR_OUT)
		return (open_redir_out(node));
	if (node->type_redir == REDIR_OUT_APPEND)
		return (open_redir_append(node));
	if (node->type_redir == REDIR_HEREDOC)
		return (open_redir_heredoc(heredoc));
	return (FAILURE);
}

static void	expand_redir(t_maindata *core_data, t_queue_redir *node)
{
	char	*tmp;

	if (node->type_redir == REDIR_HEREDOC)
	{
		return ;
	}
	if (ft_strchr((const char *)node->file_name, '~') != NULL)
		node->file_name = (void *)handle_tilde(node->file_name,
				core_data->uname);
	if (ft_strchr((const char *)node->file_name, '$') != NULL)
		node->file_name = (void *)handle_env(core_data, node->file_name);
	tmp = clean_quote(node->file_name);
	free(node->file_name);
	node->file_name = tmp;
}

int	open_redir(t_maindata *core_data, const t_ats *node)
{
	t_queue_redir	*node_redir;
	int				exit_code;
	int				index;

	index = node->data->nb_redir;
	exit_code = SUCCESS;
	while (index > 0 && exit_code == SUCCESS)
	{
		node_redir = (t_queue_redir *)ft_dequeue(core_data->queue_redir);
		if (!node_redir)
		{
			return (FAILURE);
		}
		expand_redir(core_data, node_redir);
		exit_code = open_redir_type(node_redir, core_data->queue_heredoc);
		index--;
	}
	return (exit_code);
}
