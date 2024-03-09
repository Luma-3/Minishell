/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:12:10 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/09 19:02:01 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "minishell.h"

static void	init_new_ats(t_ats *ats, t_ats *new_ats, t_bin_tree *node)
{
	new_ats->prompt = ft_strdup(node->data->cmd);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT);
	new_ats->env = ats->env;
	new_ats->queue_heredoc = ats->queue_heredoc;
	new_ats->last_status = 0;
	new_ats->queue = ft_init_queue();
	new_ats->root = NULL;
}

int	exec_subshell(t_ats *ats, t_bin_tree *node, pid_t *pid)
{
	t_ats	new_ats;
	int		status;

	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		init_new_ats(ats, &new_ats, node);
		parse_ats(new_ats.prompt, &new_ats, false);
		read_ats(&new_ats, new_ats.root);
		status = new_ats.last_status;
		clear_ats(&new_ats, true);
		exit(status);
	}
	return (SUCCESS);
}
