/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/02/16 18:01:42 by antgabri         ###   ########.fr       */
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
		path_command[ft_strlen(path_command)] = '\0';
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
	path_command[ft_strlen(path_command)] = '\0';
	return (path_command);
}

char	*get_path(char **tab)
{
	char	*path_command;
	char	**path;
	int		index;

	index = 0;
	path = ft_split(getenv("PATH"), ':');
	index = find_command_path(path, tab[0]);
	printf("index = %d\n", index);
	if (index == FAILURE)
		return (printf("C'est casse\n"), NULL);
	path_command = get_command_path(path, tab);
	if (path_command == NULL)
		return (NULL);
	else
		return (path_command);
}
