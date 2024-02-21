/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/21 13:53:34 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_prog(char **tab, char **env_tab, int i)
{
	char	cwd[4096];
	char	*path_prog;

	printf("GO to exec_prog\n");
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd failed");
		return (FAILURE);
	}
	path_prog = ft_strdup(cwd);
	char *temp = ft_strtrim(tab[i], ".");
	path_prog = ft_strjoin(path_prog, temp);
	free(temp);
	if (access(path_prog, F_OK | X_OK) == -1)
	{
		printf("access failed\n");
		print_error_message();
		free(path_prog);
		return (FAILURE);
	}
	else if (execve(path_prog, &tab[i], env_tab) == -1)
	{
		print_error_message();
		free(path_prog);
		return (FAILURE);
	}
	free(path_prog);
	printf("exec_prog done\n");
	return (SUCCESS);
}

static int	exec_command(char **tab, char *path, char **env_tab)
{
	printf("GO to exec_command\n");
	printf("path = %s\n", path);
	if (execve(path, tab, env_tab) == -1)
	{
		print_error_message();
		return (FAILURE);
	}
	return (SUCCESS);
}

int	exec(t_list *env, char *prompt)
{
	pid_t	pid;
	char	**env_tab;
	char	**tab;
	char	*path;

	tab = ft_split(prompt, ' ');
	path = get_path(tab, env, 0);
	env_tab = env_to_tab(env);
	pid = fork();
	if (pid < 0)
		return (print_error_message(), FAILURE);
	else if (pid == 0)
	{
		if (tab[0][0] == '/')
		{
			if (exec_command(tab, path, env_tab) == -1)
				return (FAILURE);
		}
		else if (tab[0][0] == '.')
			exec_prog(tab, env_tab, 0);
		else
		{
			if (exec_command(tab, path, env_tab) == -1)
				return (FAILURE);
		}	
	}
	waitpid(pid, NULL, 0);
	return (SUCCESS);
}
