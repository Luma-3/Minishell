/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:17:05 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/23 16:45:03 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_exec(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

// void	free_child(t_child *child, int nb_child)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb_child)
// 	{
// 		free(child[i]);
// 		i++;
// 	}
// 	free(child);
// }