/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/03/22 15:23:54 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "ms_error.h"

static char	*get_path_binary(char *tab)
{
	char	*cwd;
	char	*path_prog;
	char	*temp;

	cwd = NULL;
	if (getcwd(cwd, 0) == NULL)
		return (NULL);
	path_prog = ft_strdup(cwd);
	free(cwd);
	temp = ft_strtrim(tab, ".");
	path_prog = ft_strjoin(path_prog, temp);
	free(temp);
	return (path_prog);
}

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

static char	*get_path_command(char *tab, t_list *env)
{
	char	**path_command;
	char	*temp1;
	int		i;

	i = 0;
	temp1 = ms_getenv(env, "PATH");
	path_command = ft_split(temp1, ':');
	if (path_command == NULL)
		return (NULL);
	free(temp1);
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

char	*get_path(t_list *env, char *tab)
{
	char	*path;
	char	**temp;

	path = NULL;
	temp = NULL;
	if (tab[0] == '\\')
	{
		temp = ft_split(tab, ' ');
		if (temp != NULL && access(temp[0], F_OK) == SUCCESS)
			return (temp[0]);
	}
	else if (tab[0] == '.')
	{
		path = get_path_binary(tab);
		if (path != NULL && access(temp[0], X_OK) == SUCCESS)
			return (path);
	}
	else
	{
		path = get_path_command(tab, env);
		if (path != NULL && access(path, X_OK | F_OK) == SUCCESS)
			return (path);
	}
	errno = ENOCNF;
	return (NULL);
}
