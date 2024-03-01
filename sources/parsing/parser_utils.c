/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:42:27 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 11:15:08 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
/**
 * @brief Test if char is a quote type (double quote or single quote)
 * 
 * @param c char to test
 * @return true if is quote type, false is isn't quote type
*/
int	isquote_type(char c)
{
	if (c == '\'' || c == '\"')
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Place cursor after a word
 */
int	place_cursor_after_word(const char *prompt, int i)
{
	char	quote_type;

	quote_type = 0;
	while (ft_iswhitespace(prompt[i]) == true && prompt[i])
		i++;
	while (prompt[i] && ft_iswhitespace(prompt[i]) == false)
	{
		if (isquote_type(prompt[i]) == true && quote_type == 0)
		{
			if (verif_quote_delimiter(prompt, prompt[i], i + 1) == FAILURE)
				return (FAILURE);
			quote_type = prompt[i++];
			while (prompt[i] && prompt[i] != quote_type)
				i++;
			return (i + 1);
		}
		else if (isquote_type(prompt[i]) == true && quote_type != 0)
		{
			quote_type = 0;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	place_cursor_after_quote(const char *prompt, int i)
{
	char	c;

	c = prompt[i];
	i++;
	while (prompt[i] && prompt[i] != c)
		i++;
	return (i + 1);
}
