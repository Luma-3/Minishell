/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 17:54:20 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

static int	open_redir_type(t_redir_data *node, t_queue *heredoc)
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

static void	expand_redir(t_core *core_data, t_redir_data *node)
{
	char	*tmp;

	if (node->type_redir == REDIR_HEREDOC)
	{
		return ;
	}
	if (ft_strchr((const char *)node->filename, '~') != NULL)
		node->filename = (void *)handle_tilde(node->filename,
				core_data->uname);
	if (ft_strchr((const char *)node->filename, '$') != NULL)
		node->filename = (void *)handle_env(core_data, node->filename);
	tmp = clean_quote(node->filename);
	free(node->filename);
	node->filename = tmp;
}

int	open_redir(t_core *core_data, const t_ast *node)
{
	t_redir_data	*node_redir;
	int				index;

	index = node->data->nb_redir;
	while (index > 0)
	{
		node_redir = (t_redir_data *)ft_dequeue(core_data->q_redir);
		if (!node_redir)
		{
			return (FAILURE);
		}
		expand_redir(core_data, node_redir);
		if (open_redir_type(node_redir, core_data->q_kikidoc) == FAILURE)
		{
			perror_switch(core_data->errors, node_redir->filename, NULL);
			return (FAILURE);
		}
		free(node_redir->filename);
		free(node_redir);
		index--;
	}
	return (SUCCESS);
}
