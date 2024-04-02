/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 16:48:47 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"

extern volatile int	g_sigreciever;

static int	wait_process(t_maindata *core_data, t_ats *node)
{
	int	ret;

	while (true)
	{
		ret = waitpid(node->data->pid, &node->data->exit_code, WNOHANG);
		if (ret == FAILURE)
			return (FAILURE);
		if (ret == node->data->pid)
		{
			core_data->last_status = WEXITSTATUS(node->data->exit_code);
			return (SUCCESS);
		}
		if (g_sigreciever == SIGINT)
		{
			kill(node->data->pid, SIGINT);
			waitpid(node->data->pid, &node->data->exit_code, 0);
			core_data->last_status = WEXITSTATUS(node->data->exit_code);
			g_sigreciever = 0;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	read_node(t_maindata *core_data, t_ats *node, t_ats *preview_node)
{
	if (is_operator(node->data->cmd) == true)
	{
		node->data->exit_code = preview_node->data->exit_code;
		return (SUCCESS);
	}
	else if (node->data->is_subshell == true)
	{
		exec_subshell(core_data, node);
	}
	else
	{
		exec_std(core_data, node);
	}
	if (node->data->pid >= 0 && node->data->require_wait == true)
	{
		return (wait_process(core_data, node));
	}
	return (SUCCESS);
}

int	read_ats(t_maindata *core_data, t_ats *root)
{
	if (root == NULL)
		return (SUCCESS);
	if (read_ats(core_data, root->left) == FAILURE)
		return (FAILURE);
	if (read_node(core_data, root, root->left) == FAILURE)
		return (FAILURE);
	if (is_operator(root->data->cmd) == true)
	{
		if (root->data->cmd[0] == '&' && root->data->exit_code != SUCCESS)
			return (SUCCESS);
		else if (root->data->cmd[0] == '|' && root->data->exit_code == SUCCESS)
			return (SUCCESS);
		else
		{
			if (read_ats(core_data, root->right) == FAILURE)
				return (FAILURE);
		}
	}
	if (is_operator(root->data->cmd) == true)
	{
		if (read_node(core_data, root, root->right) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
