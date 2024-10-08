/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/15 12:05:01 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"
#include "redirection.h"

static void	init_new_ats(t_core *core_data, t_core *new_core,
		t_ast *node)
{
	new_core->prompt = ft_strdup(node->data->cmd);
	clear_ats(core_data, CORE_REDIR | CORE_ROOT | CORE_PROMPT | CORE_PIPE);
	new_core->env = core_data->env;
	new_core->q_kikidoc = core_data->q_kikidoc;
	new_core->last_status = 0;
	new_core->uname = core_data->uname;
	new_core->path = core_data->path;
	new_core->history_fd = -1;
	new_core->save_stdin = -1;
	new_core->errors = core_data->errors;
	new_core->q_redir = ft_init_queue();
	new_core->q_pipe = ft_init_queue();
	new_core->root = NULL;
	new_core->is_pipeline = false;
}

int	exec_subshell(t_core *core_data, t_ast *node)
{
	t_core		new_ats;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		close_fds(core_data);
		if (pre_process_exec(core_data, (t_ast *)node) == FAILURE)
			clean_child(core_data, NULL);
		close_all_pipes(core_data);
		init_new_ats(core_data, &new_ats, node);
		parse_prompt(new_ats.prompt, &new_ats, false);
		read_ats(&new_ats, new_ats.root);
		status = new_ats.last_status;
		clear_ats(&new_ats, CORE_ALL);
		exit(status);
	}
	return (clean_parent(core_data, node, NULL));
}
