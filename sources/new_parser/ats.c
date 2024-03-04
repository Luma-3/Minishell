/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 17:27:00 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static void connect_node(t_bin_tree **root, t_bin_tree *node)
{	
	if (!(*root))
	{
		*root = node;
		return ;
	}
	if (compare_token(node->data, (*root)->data) < 0)
	{
		//printf("connect_node\n");
		(*root)->right = node;
	}
}

t_bin_tree	*create_ats(t_bin_tree **root, const char *prompt, int index_offset)
{
	int	index_read;
	t_bin_tree	*node;
		
	index_read = index_offset;
	node = read_line(prompt, &index_read);
	connect_node(root, node);
	// if (is_pipe(prompt, index_read) == true)
	// {
	// 	copy_token(prompt, root, index_read, index_read + 1);
	// 	index_read++;
	// 	create_ats(root, prompt, index_read);
	// }
	return (node);
}