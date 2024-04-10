/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:55:46 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 23:30:48 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	place_cursor_parenthesis(const char *prompt, int index)
{
	int		parenthesis;

	parenthesis = 1;
	index++;
	while (prompt[index] && parenthesis != 0)
	{
		if (prompt[index] == '(')
		{
			index++;
			parenthesis++;
		}
		else if (prompt[index] == ')')
		{
			index++;
			parenthesis--;
		}
		else
			index++;
	}
	return (index);
}

int	place_cursor_quote(const char *prompt, int i)
{
	char	c;

	c = prompt[i++];
	while (prompt[i] && prompt[i] != c)
		i++;
	return (i);
}

int	place_cursor_after_token(const char *prompt, int i)
{
	char	c;

	c = prompt[i];
	while (prompt[i] == c)
		i++;
	return (i);
}

int	skip_quote_parenthesis(const char *prompt, int index)
{
	if (is_quote(prompt[index]) == true)
		index = place_cursor_quote(prompt, index);
	if (prompt[index] == '(')
		index = place_cursor_parenthesis(prompt, index);
	return (index);
}
