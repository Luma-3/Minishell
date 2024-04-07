/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/07 18:25:50 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(char **tab_cmd, t_list **env, t_error *errors, char *path)
{
	char	*path_command;
	char	**env_tab;

	path_command = get_path(path, tab_cmd[0]);
	if (path_command == NULL)
	{
		ft_perror(errors, tab_cmd[0]);
		ft_rm_split(tab_cmd);
		return (FAILURE);
	}
	env_tab = env_to_tab(*env);
	if (execve(path_command, tab_cmd, env_tab) == -1)
	{
		free(path_command);
		ft_rm_split(tab_cmd);
		ft_rm_split(env_tab);
		perror("execve");
		return (FAILURE);
	}
	return (SUCCESS);
}
