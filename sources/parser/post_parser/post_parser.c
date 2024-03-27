/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:46:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 18:24:53 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	post_parser(t_maindata *core_data, t_ats *root)
{
	if (root == NULL)
		return (SUCCESS);
	if (root->data->post_parser == true)
	{
		root->data->argv = alloc_tab(core_data, root->data->cmd);
		if (root->data->argv == NULL)
			return (FAILURE);
		// root->data->argv = handle_wildcard(core_data, root->data->argv);
	}
	post_parser(core_data, root->left);
	post_parser(core_data, root->right);
	return (SUCCESS);
}
