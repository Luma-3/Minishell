/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:51:10 by anthony           #+#    #+#             */
/*   Updated: 2024/02/27 18:00:11 by anthony          ###   ########.fr       */
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
