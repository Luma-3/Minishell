/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/15 17:22:43 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_data(char *tab, const char *prompt,
	int position, int nb_letters)
{
	int		j;
	char	char1_word;

	j = 0;
	while (ft_iswhitespace(prompt[position]) == true)
		position++;
	char1_word = prompt[position];
	while (isquote_type(prompt[position]) == true)
		position++;
	while (j < nb_letters)
	{
		if (isquote_type(char1_word) == false
			&& isquote_type(prompt[position]) == true)
			position++;
		else
		{
			tab[j] = prompt[position];
			j++;
			position++;
		}
	}
	tab[j] = '\0';
	return (tab);
}

static char	**insert_data(char **tab, const char *prompt, int nb_words)
{
	int	nb_letters;
	int	position;
	int	index;

	position = 0;
	nb_letters = 0;
	index = 0;
	while (prompt[position] && index < nb_words)
	{
		nb_letters = count_letters(prompt, position);
		printf("nb_letters = %d\n", nb_letters);
		if (nb_letters != 0)
		{
			tab[index] = malloc(sizeof(char) * (nb_letters + 1));
			if (tab[index] == NULL)
				return (NULL);//TODO free tab
			tab[index] = copy_data(tab[index], prompt, position, nb_letters);
			index++;
		}
		position = place_cursor(prompt, position);
	}
	return (tab);
}

/**
 * @brief Malloc le double tableau de char
 * @return NULL if alloc failed pointer on tab if alloc success
*/
char	**alloc_tab(char *prompt)
{
	char	**tab;
	int		nb_words;

	tab = NULL;
	nb_words = count_words(prompt);
	printf("nb_words = %d\n", nb_words);
	if (nb_words == FAILURE)
		return (NULL);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	tab[nb_words] = NULL;
	return (insert_data(tab, prompt, nb_words));
}
