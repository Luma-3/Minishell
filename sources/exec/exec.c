/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monsieurc <monsieurc@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/22 00:52:44 by monsieurc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_child	*init_child(t_child *child, int nb_child)
{
	int	i;

	i = 0;
	child = malloc(sizeof(t_child) * nb_child);
	if (child == NULL)
		return (NULL);
	while (i < nb_child)
	{
		child->fd_pipe[0] = 0;
		child->fd_pipe[1] = 1;
		child->pid = 0;
		i++;
	}
	return (child);
}

static int	exec_command(char *tab, t_list *env)
{
	char	*path_command;
	char	**env_tab;
	char	**command;

	path_command = get_path(env, tab);
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
	child = init_child(child, nb_pipe(tab));
	perror("change_fd_pipe");
	while (i < nb_pipe(tab))
	{
		perror("go to fork");
		child[i].pid = fork();
		i++;
		if (child[i].pid < 0)
			return (FAILURE);
		else if (child[i].pid == 0)
		{	
			if (dup_in_out_child(child, i, nb_pipe(tab)) == FAILURE)
				return (FAILURE);
			perror("go to exec_command");
			if (exec_command(tab[i], env) == FAILURE)
			{
				if (i != 0)
					close(child[i - 1].fd_pipe[0]);
				if (i + 1 != nb_pipe(tab))
					close(child[i].fd_pipe[1]);
			}
		}
		perror("go to i++");
	}
	perror("go to waitpid");
	i = 0;
	while (i < nb_pipe(tab))
	{
		waitpid(child[i].pid, NULL, 0);
		i++;
	}
	free(child);
	free(tab);
	return (SUCCESS);
}
