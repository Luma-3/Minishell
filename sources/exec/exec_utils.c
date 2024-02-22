/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:43:26 by monsieurc         #+#    #+#             */
/*   Updated: 2024/02/22 17:59:32 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_pipe(char **tab)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '|') != 0)
			count++;
		i++;
	}
	return (i + count);
}

t_child	*dup_in_out_child(t_child *child, int i, int nb_child)
{
	if (i != 0)
	{
		close(child[i - 1].fd_pipe[1]);
		if (dup2(child[i - 1].fd_pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2 STDIN_FILENO");
			return (NULL);
		}
		close(child[i - 1].fd_pipe[0]);
	}
	if (i + 1 != nb_child)
	{
		close(child[i].fd_pipe[0]);
		if (dup2(child[i].fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 STDOUT_FILENO");
			return (NULL);
		}
		close(child[i].fd_pipe[1]);
	}
	return (child);
}

int	close_pipe(t_child *child, int nb_child)
{
	int	i;

	i = 0;
	while (i < nb_child)
	{
		if (close(child[i].fd_pipe[0]) == -1)
		{
			perror("close 1");
			return (FAILURE);
		}
		if (close(child[i].fd_pipe[1]) == -1)
		{
			perror("close 2");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	wait_child(t_child *child, int nb_child)
{
	int	i;

	i = 0;
	while (i < nb_child)
	{
		if (waitpid(child[i].pid, NULL, 0) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	close_fd_error(t_child *child, int i, int nb_pipe)
{
	if (i != 0)
		close(child[i - 1].fd_pipe[0]);
	if (i + 1 != nb_pipe)
		close(child[i].fd_pipe[1]);
}
