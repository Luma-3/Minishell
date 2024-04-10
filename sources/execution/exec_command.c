/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/10 13:32:05 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

void	exec_command(char **tab_cmd, t_list **env, t_error *errors, char *path)
{
	struct stat	stat_path;
	char		*path_command;
	char		**env_tab;

	path_command = get_path(path, tab_cmd[0]);
	if (path_command == NULL)
	{
		perror_switch(errors, tab_cmd[0], NULL);
		return ;
	}
	if (access(path_command, F_OK) == -1)
	{
		errno = ENOENT;
		perror_switch(errors, tab_cmd[0], NULL);
		free(path_command);
		free(path);
		return ;
	}
	stat(path_command, &stat_path);
	if (S_ISDIR(stat_path.st_mode))
	{
		errno = EISDIR;
		perror_switch(errors, tab_cmd[0], NULL);
		free(path_command);
		free(path);
		return ;
	}
	env_tab = env_to_tab(*env);
	if (execve(path_command, tab_cmd, env_tab) == -1)
	{
		free(path_command);
		free(path);
		ft_rm_split(env_tab);
		perror_switch(errors, tab_cmd[0], NULL);
		return ;
	}
}
