/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/08 18:26:22 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"

pid_t	exec_std(t_ats *ats, const t_bin_tree *node, pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (FAILURE);
	else if (*pid == 0)
	{
		// if (is_builtins(node->data->argv[0]) == true)
		// {
		// 	if (exec_builtins((const char **)(node->data->argv), &(ats->env)) == FAILURE)
		// 		exit (EXIT_FAILURE);
		// 	exit (EXIT_SUCCESS); // TODO : check if exit or return
		// }
		if (open_redir(ats, node) != SUCCESS)
			exit(errno);
		if (exec_command(node->data->argv, &(ats->env)) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
