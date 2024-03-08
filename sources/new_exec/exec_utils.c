/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:43:26 by monsieurc         #+#    #+#             */
/*   Updated: 2024/03/08 12:41:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	nb_array(char **tab)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i] != NULL && ft_strchr(tab[i], '|') != 0)
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
		while (child[i].status == -2)
			i++;
		if (waitpid(child[i].pid, NULL, 0) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

