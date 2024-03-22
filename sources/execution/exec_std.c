/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 14:37:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

int	clean_parent(t_ats *ats, const t_bin_tree *node)
{
	t_queue_redir *free_queue;

	while (node->data->nb_redir > 0)
	{
		free_queue = (t_queue_redir *)ft_dequeue(ats->queue_redir);
		node->data->nb_redir--;
		if (free_queue->type_redir == REDIR_HEREDOC)
			ft_dequeue(ats->queue_heredoc);
	}
	if (node->data->index - 1 >= 0)
		return (close_pipe(ats));
	return (SUCCESS);
}

pid_t	exec_std(t_ats *ats, const t_bin_tree *node)
{
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		// TODO : handle builtins
		if (handle_pipeline(ats, node) == FAILURE)
			exit(FAILURE);
		if (open_redir(ats->queue_redir, ats->queue_heredoc, node) != SUCCESS)
			exit(FAILURE);
		if (node->data->index != -1)
			dup_pipe(ats, node->data->index);
		if (exec_command(node->data->argv, &(ats->env), ats->errors) == FAILURE)
		{
			clear_ats(ats, ATS_ALL);
			exit (FAILURE);
		}
	}
	return (clean_parent(ats, node));
}
