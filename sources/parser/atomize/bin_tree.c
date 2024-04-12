/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:10:14 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 17:37:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_ast	*create_node(t_token *data)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	find_weight(const char *data)
{
	if (ft_strncmp(data, "||", 3) == 0)
		return (WEIGHT_OR);
	else if (ft_strncmp(data, "&&", 3) == 0)
		return (WEIGHT_AND);
	return (WEIGHT_CMD);
}

int	compare_token(t_token *data1, t_token *data2)
{
	return (find_weight(data1->cmd) - find_weight(data2->cmd));
}

int	insert_node(t_ast **root, t_token *data,
					int (*cmp)(t_token *, t_token *))
{
	t_ast	*node;

	if (!(*root))
	{
		*root = create_node(data);
		if (!(*root))
			return (FAILURE);
		return (SUCCESS);
	}
	if (cmp(data, (*root)->data) < 0)
	{
		if ((*root)->left == NULL)
			return (insert_node(&(*root)->left, data, cmp));
		else
			return (insert_node(&(*root)->right, data, cmp));
	}
	else
	{
		node = create_node(data);
		if (!node)
			return (FAILURE);
		node->left = (*root);
		*root = node;
	}
	return (SUCCESS);
}

void	clear_tree(t_ast *root, void (*free_data)(void *))
{
	if (!root)
		return ;
	clear_tree(root->left, free_data);
	clear_tree(root->right, free_data);
	free_data(root->data);
	free(root);
	root = NULL;
}
