/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/08 11:21:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	read_node(t_ats *ats, t_bin_tree *node)
{
	
}

int	read_ats(t_ats *ats, t_bin_tree *root)
{
	if (root == NULL)
		return (0);
	read_ats(ats, root->left);
	// TODO : exec_cmd
	read_ats(ats, root->right);
}
