/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/16 19:03:05 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_prog(char **tab, char **env_tab)
{
	char	*path_prog;

	path_prog = NULL;
	path_prog = ft_strdup(getcwd(path_prog, sizeof(path_prog)));
	path_prog = ft_strjoin(path_prog, "/");
	path_prog = ft_strjoin(path_prog, tab[0]);
	printf("path_prog = %s\n", path_prog);
	if (execve(path_prog, tab, env_tab) == -1)
	{
		print_error_message();
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	exec_command(char **tab, char *path, char **env_tab)
{
	if (execve(path, tab, env_tab) == -1)
	{
		print_error_message();
		return (FAILURE);
	}
	return (SUCCESS);
}

int	exec(char **tab, char *path, t_list *env)
{
	pid_t	pid;
	char	**env_tab;

	env_tab = env_to_tab(env);
	pid = fork();
	printf("tab[0] = %s\n", tab[0]);
	if (pid < 0)
		return (print_error_message(), FAILURE);
	else if (pid == 0)
	{
		if (tab[0][0] != '/' && tab[0][0] != '.')
		{
			if (exec_command(tab, path, env_tab) == -1)
				return (FAILURE);
		}
		else if (tab[0][0] == '.')
			exec_prog(tab, env_tab);
		// else
		// 	exec_path(tab, path, env);//TODO
		printf("exec passage\n");
	}
	else
		waitpid(pid, NULL, 0);
	return (SUCCESS);
}
