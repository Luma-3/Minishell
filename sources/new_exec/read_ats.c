/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/08 18:44:55 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

static int	exec_subshell(t_ats *ats, t_bin_tree *node, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		parse_ats(node->data->cmd, ats, false);
		read_ats(ats, ats->root);
		exit(SUCCESS);
	}
	return (SUCCESS);
}

static int	read_node(t_ats *ats, t_bin_tree *node, pid_t *pid)
{
	if (node->data->is_subshell == true)
	{
		exec_subshell(ats, node, pid);
	}
	else if (is_token(node->data->cmd[0]) == true)
	{
		return (handle_token(ats, node, pid));
	}
	else
	{
		return (exec_std(ats, node, pid));
	}
	return (SUCCESS);
}

int	read_ats(t_ats *ats, t_bin_tree *root)
{
	static int	pid;
	int			code_status;

	code_status = CONTINUE;
	if (root == NULL)
		return (0);
	read_ats(ats, root->left);
	code_status = read_node(ats, root, &pid);
	if (code_status == CONTINUE)
		read_ats(ats, root->right);
	if (root->data->last_cmd == true)
	{
		handle_token(ats, root, &pid);
	}
	return (SUCCESS);
}
