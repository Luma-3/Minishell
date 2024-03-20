/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:46:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 11:58:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h" // TODO remove

int	post_parser(t_bin_tree	*root)
{
	if (root == NULL)
		return (SUCCESS);
	if (root->data->post_parser == true)
	{
		root->data->argv = alloc_tab(root->data->cmd);
		if (root->data->argv == NULL)
			return (FAILURE);
	}
	post_parser(root->left);
	post_parser(root->right);
	return (SUCCESS);
}
