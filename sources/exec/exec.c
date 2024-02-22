/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/22 14:30:37 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (FAILURE);
	return (SUCCESS);
}

int	launch_child(t_child *child, int nb_pipe, char **tab, t_list *env)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		child[i].pid = fork();
		if (child[i].pid < 0)
			return (FAILURE);
		else if (child[i].pid == 0)
		{
			child = dup_in_out_child(child, i, nb_pipe);
			if (child == NULL)
				return (FAILURE);
			if (exec_command(tab[i], env) == FAILURE)
				return (FAILURE);
			exit(SUCCESS);
		}
		else
			close_fd_error(child, i, nb_pipe);
		i++;
	}
	close_pipe(child, nb_pipe);
	wait_child(child, nb_pipe);
	return (SUCCESS);
}

int	exec(t_list *env, char *prompt)
{
	t_child	*child;
	char	**tab;
	int		i;

	child = NULL;
	i = 0;
	tab = ft_split(ft_strtrim(prompt, " "), '|');
	if (tab == NULL)
		return (FAILURE);
	child = init_child(child, nb_pipe(tab));
	if (child == NULL)
		return (FAILURE);
	while (i < nb_pipe(tab))
	{
		if (pipe(child[i].fd_pipe) == -1)
		{
			perror("pipe");
			return (FAILURE);
		}
		i++;
	}
	if (launch_child(child, nb_pipe(tab), tab, env) == FAILURE)
		return (FAILURE);
	free(child);
	return (SUCCESS);
}
