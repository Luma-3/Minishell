/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/02/23 15:11:12 by antgabri         ###   ########.fr       */
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
	char	*temp1;
	char	*temp2;
	int		i;

	i = 0;
	temp2 = NULL;
	temp1 = ms_getenv(env, "PATH");
	path_command = ft_split(temp1, ':');
	if (path_command == NULL)
		return (NULL);
	free(temp1);
	arg_tab = ft_split(tab, ' ');
	if (arg_tab == NULL)
		return (free_tab_exec(path_command), NULL);
	while (path_command[i])
	{
		temp1 = ft_strdup(path_command[i]);
		temp2 = ft_strjoin(temp1, "/");
		free(temp1);
		temp1 = ft_strjoin(temp2, arg_tab[0]);
		free(temp2);
		if (test_exec_prog(temp1) == SUCCESS)
			return (free_tab_exec(path_command), free_tab_exec(arg_tab), temp1);
		free(temp1);
		i++;
	}
	return (free_tab_exec(path_command),
		free_tab_exec(arg_tab), NULL);
}

char	*get_path(t_list *env, char *tab)
{
	char	*path;
	char	**temp;

	path = NULL;
	if (tab[0] == '\\')
	{
		temp = ft_split(tab, ' ');
		if (temp != NULL && test_path_access(temp[0]) == SUCCESS)
			return (temp[0]);
	}
	else if (tab[0] == '.')
	{
		path = get_path_binary(tab);
		if (path != NULL && test_exec_prog(path) == SUCCESS)
			return (path);
	}
	else
	{
		path = get_path_command(tab, env);
		if (path != NULL && access(path, X_OK | F_OK) == 0)
			return (path);
	}
	return (NULL);
}
