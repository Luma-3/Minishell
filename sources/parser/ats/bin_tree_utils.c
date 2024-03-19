/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:39:06 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 16:28:47 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	count_nodes(t_bin_tree *root, size_t count)
{
	if (!root)
		return (count);
	count++;
	count = count_nodes(root->left, count);
	count = count_nodes(root->right, count);
	return (count);
}
