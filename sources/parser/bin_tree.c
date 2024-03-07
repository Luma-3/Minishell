/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:10:14 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 11:58:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	print_inorder(t_bin_tree *root)
{
	if (!root)
		return ;
	print_inorder(root->left);
	printf("%s\n", root->data->cmd);
	print_inorder(root->right);
}

t_bin_tree	*create_node(t_token *data)
{
	t_bin_tree	*node;

	node = (t_bin_tree *)malloc(sizeof(t_bin_tree));
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
	else if (ft_strncmp(data, "|", 2) == 0)
		return (WEIGHT_PIPE);
	return (WEIGHT_CMD);
}

int	compare_token(t_token *data1, t_token *data2)
{
	return (find_weight(data1->cmd) - find_weight(data2->cmd));
}

void	insert_node(t_bin_tree **root, t_token *data,
					int (*cmp)(t_token *, t_token *))
{
	t_bin_tree	*node;

	if (!(*root))
	{
		*root = create_node(data);
		return ;
	}
	if (cmp(data, (*root)->data) < 0)
	{
		if ((*root)->left == NULL)
			insert_node(&(*root)->left, data, cmp);
		else if ((*root)->right == NULL)
			insert_node(&(*root)->right, data, cmp);
		else
			insert_node(&(*root)->right, data, cmp);
	}
	else
	{
		node = create_node(data);
		node->left = (*root);
		*root = node;
	}
}

void	clear_tree(t_bin_tree *root)
{
	if (!root)
		return ;
	clear_tree(root->left);
	clear_tree(root->right);
	free(root->data);
	free(root);
}
