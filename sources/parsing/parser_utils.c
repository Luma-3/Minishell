/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:42:27 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 13:19:43 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * @brief Place le curseur sur le debut du prochain mot
 */
int	place_cursor(const char *prompt, int i)
{
	char	c;

	c = prompt[i];
	while (prompt[i] && ft_iswhitespace(prompt[i]) == true)
		i++;
	if (c == '\'' || c == '\"')
	{
		while (prompt[i + 1] != c)
			i++;
		return (i + 2);
	}
	else
	{
		while (prompt[i] && ft_iswhitespace(prompt[i]) == false)
		{
			i++;
			if (prompt[i] == '\0')
				return (i);
		}
	}
	return (i + 1);
}
