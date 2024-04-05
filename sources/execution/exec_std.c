/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/05 18:03:57 by jbrousse         ###   ########.fr       */
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

	if (node->data->index - 1 >= 0)
		close_pipe(core_data);
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
	return (SUCCESS);
}

int	pre_process_exec(t_maindata *core_data, t_ats *node)
{
	if (handle_pipeline_redir(core_data, node) == FAILURE)
	{
		return (FAILURE);
	}
	if (open_redir(core_data, node) != SUCCESS)
	{
		return (FAILURE);
	}
	if (node->data->index != -1)
		dup_pipe(core_data, node->data->index);
	return (SUCCESS);
}



static void	process_built_out(t_maindata *core_data, t_ats *node, char **args)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		return ;
	node->data->pid = pid;
	if (pid == 0)
	{
		if (pre_process_exec(core_data, (t_ats *)node) == FAILURE)
			exit (errno);
		path = ms_getenv(core_data->env, "PATH");
		if (path == NULL)
			path = ft_strdup(core_data->path);
		close(core_data->history_fd);
		close(core_data->stdin_fd);
		exec_command(args, &(core_data->env),
			core_data->errors, path);
		clear_ats(core_data, CORE_ALL);
		exit (errno);
	}
	clean_parent(core_data, node);
}

void	exec_std(t_maindata *core_data, const t_ats *node)
{
	char	**args;

	if (node->data->cmd == NULL)
	{
		node->data->exit_code = 0;
		node->data->require_wait = false;
		return ;
	}
	args = late_parser(core_data, (t_ats *)node);
	if (args == NULL)
	{
		errno = ENOMEM;
		return ;
	}
	if (is_builtin(args[0]) == true)
	{
		process_built_in(core_data, (t_ats *)node, args);
	}
	else
	{
		process_built_out(core_data, (t_ats *)node, args);
	}
}
