/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 16:28:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"
#include "redirection.h"

static void	init_new_ats(t_ats *ats, t_ats *new_ats, t_bin_tree *node)
{
	new_ats->prompt = ft_strdup(node->data->cmd);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT);
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
	t_queue_redir	*free_queue;
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
		clear_ats(&new_ats, true);
		exit(status);
	}
	while (node->data->nb_redir > 0)
	{
		free_queue = (t_queue_redir *)ft_dequeue(ats->queue_redir);
		node->data->nb_redir--;
		if (free_queue->type_redir == REDIR_HEREDOC)
			ft_dequeue(ats->queue_heredoc);
	}
	return (SUCCESS);
}
