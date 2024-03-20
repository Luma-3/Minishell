/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 17:37:41 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

static int	read_node(t_ats *ats, t_bin_tree *node, t_bin_tree *preview_node)
{
	if (is_operator(node->data->cmd) == true)
	{
		node->data->exit_code = preview_node->data->exit_code;
		return (SUCCESS);
	}
	else if (node->data->is_subshell == true)
	{
		exec_subshell(ats, node);
	}
	else
	{
		exec_std(ats, node);
	}
	if (node->data->pid >= 0 && node->data->require_wait == true)
	{
		if (waitpid(node->data->pid, &node->data->exit_code, 0) == FAILURE)
			return (errno);
		ats->last_status = node->data->exit_code;
	}
	return (SUCCESS);
}

int	read_ats(t_ats *ats, t_bin_tree *root)
{
	int	error_return;

	if (root == NULL)
		return (SUCCESS);
	
	read_ats(ats, root->left);
	error_return = read_node(ats, root, root->left);
	if (is_operator(root->data->cmd) == true)
	{
		if (root->data->cmd[0] == '&' && root->data->exit_code != EXIT_SUCCESS)
			return (SUCCESS);
		else if (root->data->cmd[0] == '|'
			&& root->data->exit_code == EXIT_SUCCESS)
			return (SUCCESS);
		else
			read_ats(ats, root->right);
	}	
	if (is_operator(root->data->cmd) == true)
		error_return = read_node(ats, root, root->right);
	return (error_return);
}
