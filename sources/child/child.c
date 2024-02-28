/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:51:10 by anthony           #+#    #+#             */
/*   Updated: 2024/02/28 12:49:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_child	*init_child(t_child *child, int nb_child)
{
	int	i;

	i = 0;
	child = malloc(sizeof(t_child) * nb_child);
	if (child == NULL)
		return (NULL);
	while (i < nb_child)
	{
		child[i].pid = 0;
		child[i].status = 0;
		child[i].pipe_fd[0] = 0;
		child[i].pipe_fd[1] = 1;
		i++;
	}
	return (child);
}

void	dup2_read(t_child *childs, int index_child)
{
	if (dup2(childs[index_child].pipe_fd[READ], STDIN_FILENO) == FAILURE)
		perror("dup2 1");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 1");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 2");
}

void	dup2_write(t_child *childs, int index_child)
{
	if (dup2(childs[index_child].pipe_fd[WRITE], STDOUT_FILENO) == FAILURE)
		perror("dup2 2");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 3");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 4");
}
