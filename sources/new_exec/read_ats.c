/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 19:55:50 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

static int	read_node(t_ats *ats, t_bin_tree *node, pid_t *pid)
{
	if (node->data->is_subshell == true)
	{
		exec_subshell(ats, node, pid);
	}
	else if (is_operator(node->data->cmd) == true)
	{
		printf("OP\n");
		return (handle_token(ats, node, pid));
	}
	else
	{
		printf("exec_std\n");
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
		return (SUCCESS);
	read_ats(ats, root->left);
	code_status = read_node(ats, root, &pid);
	printf("cmd : %s\n", root->data->cmd);
	if (code_status == CONTINUE)
		read_ats(ats, root->right);
	if (root->data->last_cmd == true)
	{
		handle_token(ats, root, &pid);
	}
	return (SUCCESS);
}
