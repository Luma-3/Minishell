/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/21 20:32:31 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_pipe(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

static t_child	*change_fd_pipe(char **tab, t_child *child)
{
	int	i;

	i = 0;
	printf("GO TO change_fd_pipe\n");
	child = malloc(sizeof(t_child) * nb_pipe(tab));
	if (child == NULL)
		return (NULL);
	while (i < nb_pipe(tab))
	{
		pipe(child[i].fd_pipe);
		if (i != 0)
		{
			dup2(child[i - 1].fd_pipe[0], STDIN_FILENO);
			close(child[i - 1].fd_pipe[0]);
		}
		if (i + 1 != nb_pipe(tab))
		{
			dup2(child[i].fd_pipe[1], STDOUT_FILENO);
			close(child[i].fd_pipe[1]);
		}
		i++;
	}
	return (child);
}

static t_child	*init_child_alone(t_child *child)
{
	printf("GO TO init_child_alone\n");
	child = malloc(sizeof(t_child));
	if (child == NULL)
		return (NULL);
	child->fd_pipe[0] = 0;
	child->fd_pipe[1] = 1;
	return (child);
}

static int	exec_command(char *tab, t_list *env)
{
	char	*path_command;
	char	**env_tab;
	char	**command;

	printf("GO TO exec_command\n");
	path_command = get_path(env, tab);
	printf("PATH_COMMAND = %s\n", path_command);
	if (path_command == NULL)
		return (FAILURE);
	command = ft_split(tab, ' ');
	if (command == NULL)
		return (FAILURE);
	env_tab = env_to_tab(env);
	if (execve(path_command, command, env_tab) == -1)
	{
		print_error_message();
		return (FAILURE);
	}
	return (SUCCESS);
}
int	exec(t_list *env, char *prompt)
{
	t_child	*child;
	char	**tab;
	int		i;

	child = NULL;
	i = 0;
	tab = ft_split(prompt, '|');
	printf("TAB[0] = %s\n", tab[0]);
	printf("TAB[1] = %s\n", tab[1]);
	if (tab[1] != NULL)
		child = change_fd_pipe(tab, child);
	else
		child = init_child_alone(child);
	printf("CHILD IS READY\n");
	printf("nombre de pipe = %d\n", nb_pipe(tab));
	while (i < nb_pipe(tab))
	{
		printf("CHILD[%d] is alive\n", i);
		child[i].pid = fork();
		if (child[i].pid < 0)
			return (print_error_message(), FAILURE);
		else if (child[i].pid == 0)
		{
			printf("CHILD[%d] is going to exec\n", i);
			if (exec_command(tab[i], env) == FAILURE)
			{
				if (i != 0)
					close(child[i - 1].fd_pipe[0]);
				if (i + 1 != nb_pipe(tab))
					close(child[i].fd_pipe[1]);
				exit(EXIT_FAILURE);
			}
		}
		i++;
		waitpid(child[i].pid, NULL, 0);
	}
	free(child);
	free(tab);
	return (SUCCESS);
}
