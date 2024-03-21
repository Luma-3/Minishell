/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 14:49:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

static int	close_pipe(t_ats *ats)
{
	t_queue_pipe	*data;

	data = ft_dequeue(ats->queue_pipe);
	if (data == NULL)
		return (FAILURE);
	if (close(data->pipe_fd[READ]) == FAILURE)
		return (FAILURE);
	if (close(data->pipe_fd[WRITE]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	open_all_redir(t_queue *redir, t_queue *heredoc, t_bin_tree *root)
{
	if (!root)
		return (SUCCESS);
	open_all_redir(redir, heredoc, root->left);
	return (open_redir(redir, heredoc, root));
}

static t_queue	*ft_dup_queue(t_queue *queue)
{
	t_node	*tmp;
	t_queue	*new_queue;

	tmp = queue->first;
	new_queue = ft_init_queue();
	if (!new_queue)
		return (NULL);
	while (tmp)
	{
		ft_enqueue(new_queue, tmp->content);
		tmp = tmp->next;
	}
	return (new_queue);
}

pid_t	exec_std(t_ats *ats, const t_bin_tree *node)
{
	pid_t			pid;
	t_queue			*tmp_redir;
	t_queue			*tmp_heredoc;
	t_queue_redir	*free_queue;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		
		// if (is_builtins(node->data->argv[0]) == true)
		// {
		// 	if (exec_builtins((const char **)(node->data->argv), &(ats->env)) == FAILURE)
		// 		exit (EXIT_FAILURE);
		// 	exit (EXIT_SUCCESS); // TODO : check if exit or return
		// }
		if (node->data->index == 0)
		{
			tmp_redir = ft_dup_queue(ats->queue_redir);
			tmp_heredoc = ft_dup_queue(ats->queue_heredoc);
			if (!tmp_redir || !tmp_heredoc)
				return (FAILURE);
			open_all_redir(tmp_redir, tmp_heredoc, ats->root);
		}
		if (open_redir(ats->queue_redir, ats->queue_heredoc, node) != SUCCESS)
		{
			exit(FAILURE);
		}
		if (node->data->index != -1)
			dup_pipe(ats, node->data->index);
		if (exec_command(node->data->argv, &(ats->env)) == FAILURE)
			exit (FAILURE);
	}
	while (node->data->nb_redir > 0)
	{
		free_queue = (t_queue_redir *)ft_dequeue(ats->queue_redir);
		node->data->nb_redir--;
		if (free_queue->type_redir == REDIR_HEREDOC)
			ft_dequeue(ats->queue_heredoc);
	}
	if (node->data->index - 1 >= 0)
		close_pipe(ats);
	return (SUCCESS);
}
