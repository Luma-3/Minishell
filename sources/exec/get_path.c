/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/02/21 12:15:32 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_command_path(char **path, char *command)
{
	int		i;
	char	*path_command;

	i = 0;
	while (path[i])
	{
		path_command = ft_strdup(path[i]);
		path_command = ft_strjoin(path_command, "/");
		path_command = ft_strjoin(path_command, command);
		if (access(path_command, X_OK | F_OK) == 0)
			return (i);
		i++;
	}
	print_error_message();
	return (FAILURE);
}

static char	*get_command_path(char **path, char **tab)
{
	char	*command;
	char	*path_command;

	command = tab[0];
	path_command = ft_strdup(path[find_command_path(path, command)]);
	path_command = ft_strjoin(path_command, "/");
	path_command = ft_strjoin(path_command, command);
	return (path_command);
}

static int	test_path(char **tab, int i)
{
	if (access(tab[i], X_OK | F_OK) == 0)
		return (i);
	else
	{
		print_error_message();
		return (FAILURE);
	}
}

static int	test_exec_prog(char **tab, int i)
{
	if (access(tab[i], X_OK | F_OK) == 0)
		return (SUCCESS);
	else
	{
		print_error_message();
		return (FAILURE);
	}
}

char	*get_path(char **tab, t_list *env, int i)
{
	char	*path_command;
	char	**path;
	int		index;

	index = 0;
	if (tab[i][0] == '/')
	{
		if (test_path(tab, i) == FAILURE)
			return (NULL);
	}
	else if (tab[i][0] == '.')
	{
		if (test_exec_prog(tab, i) == FAILURE)
			return (NULL);
	}
	else
	{
		path = ft_split(ms_getenv(env, "PATH"), ':');
		index = find_command_path(path, tab[0]);
		if (index == FAILURE)
			return (NULL);
		path_command = get_command_path(path, tab);
		if (path_command == NULL)
			return (NULL);
		else
			return (path_command);
	}
	return (tab[i]);
}
