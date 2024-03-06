/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:49:09 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/05 17:01:50 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int place_cursor_after_parenthesis(const char *prompt, int index)
{
	int		parenthesis;

	parenthesis = 1;
	index++;
	while (prompt[index] && parenthesis != 0)
	{
		if (prompt[index] == '(')
			parenthesis++;
		else if (prompt[index] == ')')
			parenthesis--;
		index++;
	}
	return (index);
}

int	is_parenthesis(const char token)
{
	if (token == '(' || token == ')')
		return (true);
	return (false);
}

int is_pipe(const char *prompt, int index)
{
	if (prompt[index] == '|' && prompt[index + 1] != '|')
		return (true);
	return (false);
}

int is_token(char token)
{
	if (token == '|' || token == '&')
		return (true);
	return (false);
}