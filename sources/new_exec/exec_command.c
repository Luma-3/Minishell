/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/20 16:09:48 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(char **tab_cmd, t_list **env)
{
	char	*path_command;
	char	**env_tab;

	path_command = get_path(*env, tab_cmd[0]);
	if (path_command == NULL)
	{
		return (free(tab_cmd), FAILURE);
	}
	env_tab = env_to_tab(*env);
	if (execve(path_command, tab_cmd, env_tab) == -1)
	{
		ft_rm_split(env_tab);
		return (free(path_command), ft_rm_split(tab_cmd), FAILURE);
		 // TODO : check free
	}
	return (SUCCESS);
}
