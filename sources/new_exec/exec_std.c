/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:03:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 09:20:51 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"
#include "redirection.h"

pid_t	exec_std(t_ats *ats, const t_bin_tree *node)
{
	pid_t		pid;

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
		if (open_redir(ats, node) != SUCCESS)
			exit(errno);
		// if (open_pipe(ats, node) != SUCCESS)
		// 	exit(errno);
		if (exec_command(node->data->argv, &(ats->env)) == FAILURE)
		{
			printf("EXEC COMMAND FAILURE\n");
			exit (FAILURE);
		}
	}
	return (SUCCESS);
}
