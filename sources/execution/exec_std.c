/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:18:31 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"
#include "parser.h"

int	pre_process_exec(t_core *core_data, t_ast *node)
{
	handle_pipeline_redir(core_data);
	if (open_redir(core_data, node) != SUCCESS)
	{
		return (FAILURE);
	}
	if (node->data->index != -1)
		dup_pipe(core_data, node->data->index);
	return (SUCCESS);
}

static int	process_built_out(t_core *core, t_ast *node, char **args)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
	{
		ft_rm_split(args);
		perror_switch(core->errors, "kikishell", NULL);
		return (FAILURE);
	}
	node->data->pid = pid;
	if (pid == 0)
	{
		if (pre_process_exec(core, node) == FAILURE || args == NULL)
			clean_child(core, args);
		close_fds(core);
		path = ms_getenv(core->env, "PATH");
		if (path == NULL)
			path = ft_strdup(core->path);
		close_all_pipes(core);
		exec_command(args, &(core->env), core->errors, path);
		clean_child(core, args);
	}
	clean_parent(core, node, args);
	return (SUCCESS);
}

int	exec_std(t_core *core_data, const t_ast *node)
{
	char	**args;

	args = late_parser(core_data, (t_ast *)node);
	if (errno != 0 && args == NULL)
	{
		perror_switch(core_data->errors, "kikishell", NULL);
		return (FAILURE);
	}
	if (args != NULL && is_builtin(args[0]) == true)
	{
		return (process_built_in(core_data, (t_ast *)node, args));
	}
	else
	{
		return (process_built_out(core_data, (t_ast *)node, args));
	}
	return (SUCCESS);
}
