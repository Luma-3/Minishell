/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 16:56:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_words_without_quote(const char *prompt, int i)
{
	while (prompt[i] && ft_iswhitespace(prompt[i]) == false)
	{
		if (is_quote_type(prompt[i]) == true)
			break ;
		else
			i++;
	}
	return (i);
}

int	count_words(const char *prompt)
{
	int	nb_words;
	int	i;

	i = 0;
	nb_words = 0;
	while (prompt[i] != '\0')
	{
		i = ft_skip_whitespaces(prompt, i);
		if (prompt[i] == '\0')
			break ;
		if (is_quote_type(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		else
			i = count_words_without_quote(prompt, i);
		if (prompt[i] == '\0' || ft_iswhitespace(prompt[i]) == true)
			nb_words++;
	}
	return (nb_words);
}

int	count_letters(const char *start_word)
{
	int	i;

	i = 0;
	while (start_word[i])
	{
		if (ft_iswhitespace(start_word[i]) == true)
			break ;
		else if (is_quote_type(start_word[i]) == true)
			i = place_cursor_quote(start_word, i);
		else
			i++;
	}
	return (i);
}
