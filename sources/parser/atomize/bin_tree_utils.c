/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:39:06 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 14:13:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	count_nodes(t_ast *root, size_t count)
{
	if (!root)
		return (count);
	count++;
	count = count_nodes(root->left, count);
	count = count_nodes(root->right, count);
	return (count);
}
