/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/07 17:40:25 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static void	copy_word_clean(const char *word, char *new_word)
{
	int		i;
	int		j;
	char	quote_type;

	quote_type = 0;
	i = 0;
	j = 0;
	while (word[i])
	{
		if (quote_type == 0 && (word[i] == '\"' || word[i] == '\''))
			quote_type = word[i++];
		else if (word[i] == quote_type)
		{
			quote_type = 0;
			i++;
		}
		if (is_quote_type(word[i]) == false || quote_type != 0)
			new_word[j++] = word[i++];
	}
}

static int	count_quote(const char *word)
{
	int		i;
	int		count;
	char	quote_type;

	i = 0;
	count = 0;
	quote_type = 0;
	while (word[i])
	{
		if (quote_type == 0 && (word[i] == '\"' || word[i] == '\''))
			quote_type = word[i];
		else if (word[i] == quote_type)
		{
			count += 2;
			quote_type = 0;
		}
		i++;
	}
	return (count);
}

static char	*clean_quote(char *word)
{
	char	*new_word;
	int		nb_quote;

	nb_quote = count_quote(word);
	if (nb_quote == 0)
		return (word);
	new_word = (char *)ft_calloc(ft_strlen(word) - nb_quote + 1, sizeof(char));
	if (new_word == NULL)
		return (NULL);
	copy_word_clean(word, new_word);
	free(word);
	return (new_word);
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
		nb_letters = count_letters(&prompt[position]);
		if (nb_letters != 0)
		{
			tab[index] = ft_strndup(&prompt[position], nb_letters);
			tab[index] = clean_quote(tab[index]);
			position += nb_letters;
			index++;
		}
	}
	return (tab);
}

char	**alloc_tab(char *prompt)
{
	char	**tab;
	int		nb_words;

	tab = NULL;
	nb_words = count_words(prompt);
	tab = (char **)ft_calloc(nb_words + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[nb_words] = NULL;
	return (insert_data(tab, prompt, nb_words));
}
