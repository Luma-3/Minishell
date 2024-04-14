/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:01:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 14:58:47 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"

extern volatile int	g_sigreceiver;

static int	sig_handler(t_maindata *core, t_ast *node, bool is_pipeline)
{
	if (g_sigreceiver == SIGQUIT)
		printf("\r^\\\033[0KQuit (Core dumped)\n");
	if (is_pipeline == true)
	{
		while (node->left != NULL)
		{
			kill(node->data->pid, g_sigreceiver);
			waitpid(node->data->pid, &node->data->exit_code, 0);
			node = node->left;
		}
	}
	else
	{
		kill(node->data->pid, g_sigreceiver);
		waitpid(node->data->pid, &node->data->exit_code, 0);
	}
	core->last_status = g_sigreceiver;
	g_sigreceiver = 0;
	return (FAILURE);
}

static int	wait_pipeline(t_maindata *core, t_ast *node)
{
	int	ret;

	ret = 0;
	while (ret >= 0)
	{
		ret = wait3(NULL, WNOHANG, NULL);
		if (ret == FAILURE)
			return (FAILURE);
		if (g_sigreceiver != 0)
		{
			return (sig_handler(core, node, true));
		}
	}
	core->last_status = WEXITSTATUS(node->data->exit_code);
	return (SUCCESS);
}

static int	wait_process(t_maindata *core, t_ast *node)
{
	int	ret;

	ret = 0;
	if (core->is_pipeline == true && node->data->require_wait == true)
		return (wait_pipeline(core, node));
	while (ret == 0)
	{
		ret = waitpid(node->data->pid, &node->data->exit_code, WNOHANG);
		if (ret == FAILURE)
			return (FAILURE);
		if (ret == node->data->pid)
		{
			core->last_status = WEXITSTATUS(node->data->exit_code);
			return (SUCCESS);
		}
		if (g_sigreceiver != 0)
		{
			return (sig_handler(core, node, false));
		}
	}
	return (SUCCESS);
}

static int	read_node(t_maindata *core_data, t_ast *node, t_ast *preview_node)
{
	int	ret;

	ret = 0;
	if (is_operator(node->data->cmd) == true)
	{
		node->data->exit_code = preview_node->data->exit_code;
		return (SUCCESS);
	}
	else if (node->data->is_subshell == true)
	{
		ret = exec_subshell(core_data, node);
	}
	else
	{
		ret = exec_std(core_data, node);
	}
	if (node->data->pid >= 0 && node->data->require_wait == true
		&& ret == SUCCESS)
		return (wait_process(core_data, node));
	else
		core_data->last_status = node->data->exit_code;
	return (ret);
}

int	read_ats(t_maindata *core_data, t_ast *root)
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
