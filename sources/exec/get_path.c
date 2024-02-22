/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/02/22 14:26:15 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_path_access(char *tab)
{
	if (access(tab, X_OK | F_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}

static int	test_exec_prog(char *tab)
{
	if (access(tab, X_OK | F_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}

static char	*get_path_binary(char *tab)
{
	char	cwd[4096];
	char	*path_prog;
	char	*temp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(tab)));
	if (temp == NULL)
		return (NULL);
	path_prog = ft_strdup(cwd);
	temp = ft_strtrim(tab, ".");
	path_prog = ft_strjoin(path_prog, temp);
	free(temp);
	return (path_prog);
}

static char	*get_path_command(char *tab, t_list *env)
{
	char	**path_command;
	char	**arg_tab;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	path_command = ft_split(ms_getenv(env, "PATH"), ':');
	if (path_command == NULL)
		return (NULL);
	arg_tab = ft_split(tab, ' ');
	if (arg_tab == NULL)
		return (NULL);
	while (path_command[i])
	{
		temp = ft_strdup(path_command[i]);
		temp = ft_strjoin(temp, "/");
		temp = ft_strjoin(temp, arg_tab[0]);
		if (temp == NULL)
			return (NULL);
		if (test_exec_prog(temp) == SUCCESS)
			return (free(path_command), temp);
		i++;
	}
	return (NULL);
}

char	*get_path(t_list *env, char *tab)
{
	char	*path;
	char	**temp;

	if (tab[0] == '\\')
	{
		temp = ft_split(tab, ' ');
		if (test_path_access(temp[0]) == SUCCESS)
			return (temp[0]);
	}
	else if (tab[0] == '.')
	{
		path = get_path_binary(tab);
		if (test_exec_prog(path) == SUCCESS)
			return (path);
	}
	else
	{
		path = get_path_command(tab, env);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
	}
	return (NULL);
}
