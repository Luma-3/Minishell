/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/29 17:20:04 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static void	free_tab(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

static char	*copy_data(char *tab, const char *prompt,
	int position, int nb_letters)
{
	int		j;
	char	quote_type;

	j = 0;
	quote_type = 0;
	(void)nb_letters;
	// printf("Go to copy data\n");
	while (ft_iswhitespace(prompt[position]) == true)
		position++;
	if (isquote_type(prompt[position]) == true)
	{
		quote_type = prompt[position];
		position++;
	}
	while (prompt[position] && ft_iswhitespace(prompt[position]) == false)
	{
		if (quote_type != 0 && isquote_type(prompt[position]) == true
			&& prompt[position] == quote_type)
			break ;
		else if (quote_type == 0 && isquote_type(prompt[position]) == true)
		{
			quote_type = prompt[position];
			position++;
			while (prompt[position] && prompt[position] != quote_type)
			{
				tab[j] = prompt[position];
				j++;
				position++;
			}
			break ;
		}
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
		// printf("nb_letters = %d\n", nb_letters);
		if (nb_letters != 0)
		{
			tab[index] = (char *)ft_calloc(nb_letters + 1, sizeof(char));
			if (tab[index] == NULL)
			{
				free_tab(tab, index);
				return (NULL);
			}
			tab[index] = copy_data(tab[index], prompt, position, nb_letters);
			index++;
		}
		if (isquote_type(prompt[position]) == true)
			position += nb_letters + 2;
		else
			position += nb_letters + 1;
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
	if (nb_words == FAILURE)
		return (NULL);
	// printf("nb_words = %d\n", nb_words);
	tab = (char **)ft_calloc(nb_words + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[nb_words] = NULL;
	return (insert_data(tab, prompt, nb_words));
}
