/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/01 17:21:34 by antgabri         ###   ########.fr       */
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

static char	*copy_quote_in_word(char *tab, const char
	*prompt, char quote_type, int j)
{
	while (prompt && *prompt != quote_type)
	{
		tab[j++] = *prompt++;
	}
	tab[j] = '\0';
	return (tab);
}

static char	*copy_data(char *tab, const char *prompt, int position)
{
	int		j;
	char	quote_type;

	j = 0;
	quote_type = 0;
	while (ft_iswhitespace(prompt[position]) == true)
		position++;
	if (isquote_type(prompt[position]) == true)
		quote_type = prompt[position++];
	while (prompt[position] && ft_iswhitespace(prompt[position]) == false)
	{
		if (quote_type != 0)
			return (copy_quote_in_word(tab, &prompt[position], quote_type, j));
		else if (quote_type == 0 && isquote_type(prompt[position]) == true)
		{
			quote_type = prompt[position];
			position++;
			return (copy_quote_in_word(tab, &prompt[position], quote_type, j));
		}
		else
			tab[j++] = prompt[position++];
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
		position = ft_skip_whitespaces(prompt, position);
		nb_letters = count_letters(prompt, position);
		if (nb_letters != 0)
		{
			tab[index] = (char *)ft_calloc(nb_letters + 1, sizeof(char));
			if (tab[index] == NULL)
				return (free_tab(tab, index), NULL);
			tab[index] = copy_data(tab[index], prompt, position);
			index++;
		}
		if (isquote_type(prompt[position]) == true)
			position += nb_letters + 2;
		else
			position += nb_letters;
	}
	return (tab);
}

/**
 * @brief Malloc double char tab and copy data in it
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
	tab = (char **)ft_calloc(nb_words + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[nb_words] = NULL;
	return (insert_data(tab, prompt, nb_words));
}
