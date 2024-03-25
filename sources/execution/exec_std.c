/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 20:28:13 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

int	clean_parent(t_maindata *ats, const t_ats *node)
{
	t_queue_redir	*free_data_redir;
	t_queue_heredoc	*free_data_heredoc;

	while (node->data->nb_redir > 0)
	{
		free_data_redir = (t_queue_redir *)ft_dequeue(ats->queue_redir);
		node->data->nb_redir--;
		if (free_data_redir->type_redir == REDIR_HEREDOC)
		{
			free_data_heredoc = ft_dequeue(ats->queue_heredoc);
			free(free_data_heredoc->file_name);
			free(free_data_heredoc->delimiter);
			free(free_data_heredoc);
		}
		free(free_data_redir->file_name);
		free(free_data_redir);
	}
	if (node->data->index - 1 >= 0)
		return (close_pipe(ats));
	return (SUCCESS);
}

pid_t	exec_std(t_maindata *ats, const t_ats *node)
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
