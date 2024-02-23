/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:43:26 by monsieurc         #+#    #+#             */
/*   Updated: 2024/02/23 12:06:16 by antgabri         ###   ########.fr       */
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
