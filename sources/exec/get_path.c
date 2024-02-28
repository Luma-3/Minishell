/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:47:27 by Monsieur_Ca       #+#    #+#             */
/*   Updated: 2024/02/28 16:06:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"

static char	*get_path_binary(char *tab)
{
	char	cwd[4096]; // TODO: replace By another method
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
	char	**arg_tab;
	char	*temp1;
	int		i;

	i = 0;
	temp1 = ms_getenv(env, "PATH");
	path_command = ft_split(temp1, ':');
	if (path_command == NULL)
		return (NULL);
	free(temp1);
	arg_tab = ft_split(tab, ' ');
	if (arg_tab == NULL)
		return (ft_rm_split(path_command), NULL);
	while (path_command[i])
	{
		temp1 = create_path(path_command[i], arg_tab[0]);
		if (test_exec_prog(temp1) == SUCCESS)
			return (ft_rm_split(path_command), ft_rm_split(arg_tab), temp1);
		free(temp1);
		i++;
	}
	return (ft_rm_split(path_command), ft_rm_split(arg_tab), NULL);
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
