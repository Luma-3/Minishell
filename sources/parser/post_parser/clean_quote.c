/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:39:12 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 13:33:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		if (is_quote(word[i]) == false || quote_type != 0)
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

char	*clean_quote(char *word)
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
