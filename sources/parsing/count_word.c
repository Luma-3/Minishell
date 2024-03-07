/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 11:54:56 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int	verif_quote_delimiter(const char *prompt, char delimiter, int i)
{
	while (prompt[i] != delimiter)
	{
		if (prompt[i] == '\0')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	is_empty_quote(const char *prompt, char delimiter, int i)
{
	if (prompt[i] != delimiter)
	{
		return (true);
	}
	return (false);
}

static int	count_words_without_quote(const char *prompt, int i)
{
	char	quote_type;

	quote_type = 0;
	while (prompt[i] && ft_iswhitespace(prompt[i]) == false)
	{
		if (quote_type != 0 && is_quote_type(prompt[i]) == true
			&& prompt[i] == quote_type)
			break ;
		else if (quote_type == 0 && is_quote_type(prompt[i]) == true)
		{
			quote_type = prompt[i];
			i++;
			while (prompt[i] && prompt[i] != quote_type)
				i++;
			break ;
		}
		else
			i++;
	}
	return (SUCCESS);
}

static int	verify_quote(const char *prompt, int i)
{
	if (verif_quote_delimiter(prompt, prompt[i], i + 1) == FAILURE)
		return (FAILURE);
	if (is_empty_quote(prompt, prompt[i], i + 1) == true)
		return (true);
	return (false);
}

/**
 * @brief Count the number of words in a prompt
 */
int	count_words(const char *prompt)
{
	int	nb_words;
	int	i;

	i = 0;
	nb_words = 0;
	while (prompt[i] != '\0')
	{
		i = ft_skip_whitespaces(prompt, i);
		if (is_quote_type(prompt[i]) == true)
		{
			if (verify_quote(prompt, i) == FAILURE)
				return (FAILURE);
			nb_words++;
		}
		else
		{
			if (count_words_without_quote(prompt, i) == FAILURE)
				return (FAILURE);
			nb_words++;
		}
		if (is_quote_type(prompt[i]) == true)
			i = place_cursor_after_quote(prompt, i);
		i = place_cursor_after_word(prompt, i);
	}
	return (nb_words);
}
