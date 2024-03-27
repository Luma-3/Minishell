/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/03/27 12:52:55 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "ms_error.h"

static char	*create_path(char *path, char *arg)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(path);
	temp2 = ft_strjoin(temp1, "/");
	free(temp1);
	temp1 = ft_strjoin(temp2, arg);
	free(temp2);
	return (temp1);
}

static char	*get_path_command(char *path, char *tab)
{
	char	**path_command;
	char	*temp1;
	int		i;

	i = 0;
	path_command = ft_split(path, ':');
	if (path_command == NULL)
		return (NULL);
	while (path_command[i])
	{
		temp1 = create_path(path_command[i], tab);
		if (access(temp1, X_OK) == SUCCESS)
			return (ft_rm_split(path_command), temp1);
		free(temp1);
		i++;
	}
	return (ft_rm_split(path_command), NULL);
}

static int	is_path(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

static char	*path_to_relative(char *tab)
{
	char	*temp;

	temp = ft_strjoin("./", tab);
	if (temp == NULL)
		return (NULL);
	if (access(temp, X_OK) == SUCCESS)
		return (temp);
	return (NULL);
}

char	*get_path(char *path, char *tab)
{
	char	*cmd_path;

	if (tab[0] == '/' || ft_strncmp(tab, "./", 2) == 0)
		return (tab);
	else
	{
		if (is_path(tab) == true)
		{
			return (path_to_relative(tab));
		}
		cmd_path = get_path_command(path, tab);
		free(path);
		if (cmd_path != NULL && access(cmd_path, X_OK | F_OK) == SUCCESS)
			return (cmd_path);
	}
	errno = ENOCNF;
	return (NULL);
}
