/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/14 18:19:46 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
 * @brief Malloc le double tableau de char
 * @return SUCCESS ou FAILURE
 */
int	alloc_tab(char ***tab, char *prompt)
{
	int	size;
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	size = count_words(prompt);
	if (size == FAILURE)
		return (FAILURE);
	*tab = malloc(sizeof(char *) * (size + 1));
	if (*tab == NULL)
		return (FAILURE);
	(*tab)[size] = NULL;
	while (i < size)
	{
		size = count_letters(prompt, i);
		if (size != 0)
		{
			(*tab)[i] = malloc(sizeof(char) * (count_letters(prompt, i) + 1));
			if ((*tab)[i] == NULL)
				return (FAILURE);//TODO free tab
			//TODO COPY_TAB
			pos = place_cursor(prompt, i);
		}
		i++;
	}
	return (SUCCESS);
}

