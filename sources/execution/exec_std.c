/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 17:01:36 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

int	clean_parent(t_maindata *core_data, const t_ats *node)
{
	t_queue_redir	*free_data_redir;
	t_queue_heredoc	*free_data_heredoc;

	while (node->data->nb_redir > 0)
	{
		free_data_redir = (t_queue_redir *)ft_dequeue(core_data->queue_redir);
		node->data->nb_redir--;
		if (free_data_redir->type_redir == REDIR_HEREDOC)
		{
			free_data_heredoc = ft_dequeue(core_data->queue_heredoc);
			free(free_data_heredoc->file_name);
			free(free_data_heredoc->delimiter);
			free(free_data_heredoc);
		}
		free(free_data_redir->file_name);
		free(free_data_redir);
	}
	if (node->data->index - 1 >= 0)
		return (close_pipe(core_data));
	return (SUCCESS);
}

char	**pre_process_exec(t_maindata *core_data, t_ats *node)
{
	char	**args;

	args = late_parser(core_data, node);
	if (handle_pipeline(core_data, node) == FAILURE)
	{
		clear_ats(core_data, CORE_ALL);
		exit(FAILURE);
	}
	if (open_redir(core_data->queue_redir, core_data->queue_heredoc,
			node) != SUCCESS)
	{
		clear_ats(core_data, CORE_ALL);
		exit(FAILURE);
	}
	if (node->data->index != -1)
		dup_pipe(core_data, node->data->index);
	return (args);
}

pid_t	exec_std(t_maindata *core_data, const t_ats *node)
{
	pid_t	pid;
	char	*path;
	char	**args;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	node->data->pid = pid;
	if (pid == 0)
	{
		// TODO : handle builtins
		args = pre_process_exec(core_data, (t_ats *)node);
		path = ms_getenv(core_data->env, "PATH");
		if (path == NULL)
			path = ft_strdup(core_data->path);
		exec_command(args, &(core_data->env),
			core_data->errors, path);
		clear_ats(core_data, CORE_ALL);
		exit (errno);
	}
	return (clean_parent(core_data, node));
}
