/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/26 17:56:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(char **tab_cmd, t_list *env)
{
	char	*path_command;
	char	**env_tab;

	
	printf("OK\n");
	path_command = get_path(env, tab_cmd[0]);
	if (path_command == NULL)
		return (free(tab_cmd), FAILURE);
	printf("path_command = %s\n", path_command);
	env_tab = env_to_tab(env);
	if (execve(path_command, tab_cmd, env_tab) == -1)
		return (free(path_command), free(tab_cmd), FAILURE);
	return (SUCCESS);
}
