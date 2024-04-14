/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/12 19:35:41 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

static void	error_return(t_error *errors, char **tab_cmd,
	char *path_command, char *path)
{
	free(path_command);
	free(path);
	perror_switch(errors, tab_cmd[0], NULL);
}

static int	execute_command(char **tab_cmd, t_list **env, char *path,
	char *path_command)
{
	char	**env_tab;

	env_tab = env_to_tab(*env);
	if (execve(path_command, tab_cmd, env_tab) == -1)
	{
		return (ft_rm_split(env_tab), FAILURE);
	}
	ft_rm_split(env_tab);
	free(path_command);
	free(path);
	return (SUCCESS);
}

void	exec_command(char **tab_cmd, t_list **env, t_error *errors, char *path)
{
	struct stat	stat_path;
	char		*path_command;

	if (path == NULL)
	{
		errno = ENOCNF;
		return (perror_switch(errors, tab_cmd[0], NULL));
	}
	path_command = get_path(path, tab_cmd[0]);
	if (path_command == NULL)
		return (perror_switch(errors, tab_cmd[0], NULL));
	if (access(path_command, F_OK) == -1)
	{
		errno = ENOENT;
		return (error_return(errors, tab_cmd, path_command, path));
	}
	stat(path_command, &stat_path);
	if (S_ISDIR(stat_path.st_mode))
	{
		errno = EISDIR;
		return (error_return(errors, tab_cmd, path_command, path));
	}
	if (execute_command(tab_cmd, env, path, path_command) == FAILURE)
		return (error_return(errors, tab_cmd, path_command, path));
}
