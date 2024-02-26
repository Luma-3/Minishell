/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:03:33 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/26 10:45:23 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_child *child, int i, int nb_pipe)
{
	if (i != 0)
	{
		if (close(child[i - 1].fd_pipe[0]) == -1)
			perror("close");
	}
	if (i + 1 != nb_pipe)
	{
		if (close(child[i].fd_pipe[1]) == -1)
			perror("close");
	}
}

t_child	*create_pipe(t_child *child, int count_pipe)
{
	int	i;

	i = 0;
	while (i < count_pipe)
	{
		if (pipe(child[i].fd_pipe) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (child);
}

t_child	*connect_pipe(t_child *child, int i, int nb_child)
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
