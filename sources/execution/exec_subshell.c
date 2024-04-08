/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/08 16:34:24 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"
#include "redirection.h"

static void	init_new_ats(t_maindata *core_data, t_maindata *new_core,
		t_ats *node)
{
	new_core->prompt = ft_strdup(node->data->cmd);
	clear_ats(core_data, CORE_REDIR | CORE_ROOT | CORE_PROMPT | CORE_PIPE);
	new_core->env = core_data->env;
	new_core->queue_heredoc = core_data->queue_heredoc;
	new_core->last_status = 0;
	new_core->uname = core_data->uname;
	new_core->path = core_data->path;
	new_core->history_fd =  -1;
	new_core->stdin_fd = -1;
	new_core->errors = core_data->errors;
	new_core->queue_redir = ft_init_queue();
	new_core->queue_pipe = ft_init_queue();
	new_core->root = NULL;
	new_core->is_pipeline = false;
}

int	exec_subshell(t_maindata *core_data, t_ats *node)
{
	t_maindata		new_ats;
	pid_t			pid;
	int				status;

	pid = fork();
	if (pid == -1)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		close(core_data->stdin_fd);
		close(core_data->history_fd);
		open_redir(core_data, node);
		close_all_pipes(core_data);
		init_new_ats(core_data, &new_ats, node);
		parse_prompt(new_ats.prompt, &new_ats, false);
		read_ats(&new_ats, new_ats.root);
		status = new_ats.last_status;
		clear_ats(&new_ats, CORE_ALL);
		exit(status);
	}
	return (clean_parent(core_data, node));
}
