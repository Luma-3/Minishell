/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monsieurc <monsieurc@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:43:26 by monsieurc         #+#    #+#             */
/*   Updated: 2024/02/22 00:52:34 by monsieurc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_pipe(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

int dup_in_out_child(t_child *child, int i, int nb_child)
{
    if (i != 0)
    {
        close(child[i - 1].fd_pipe[1]);
        dup2(child[i - 1].fd_pipe[0], STDIN_FILENO);
    }
    if (i + 1 != nb_child)
    {
        close(child[i].fd_pipe[0]);
        dup2(child[i].fd_pipe[1], STDOUT_FILENO);
    }
    return (SUCCESS);
}