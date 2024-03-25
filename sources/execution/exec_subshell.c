/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 12:23:55 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"
#include "redirection.h"

static void	init_new_ats(t_ats *ats, t_ats *new_ats, t_bin_tree *node)
{
	new_ats->prompt = ft_strdup(node->data->cmd);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_PIPE);
	new_ats->env = ats->env;
	new_ats->queue_heredoc = ats->queue_heredoc;
	new_ats->last_status = 0;
	new_ats->queue_redir = ft_init_queue();
	new_ats->queue_pipe = ft_init_queue();
	new_ats->root = NULL;
}

int	exec_subshell(t_ats *ats, t_bin_tree *node)
{
	t_ats			new_ats;
	pid_t			pid;
	int				status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		open_redir(ats->queue_redir, ats->queue_heredoc, node);
		init_new_ats(ats, &new_ats, node);
		parse_ats(new_ats.prompt, &new_ats, false);
		read_ats(&new_ats, new_ats.root);
		status = new_ats.last_status;
		clear_ats(&new_ats, ATS_ALL);
		exit(status);
	}
	return (clean_parent(ats, node));
}
