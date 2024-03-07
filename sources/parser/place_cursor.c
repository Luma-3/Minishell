/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:55:46 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 11:56:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	place_cursor_after_parenthesis(const char *prompt, int index)
{
	int		parenthesis;

	parenthesis = 1;
	index++;
	while (prompt[index] && parenthesis != 0)
	{
		if (prompt[index] == '(')
		{
			parenthesis++;
		}
		else if (prompt[index] == ')')
		{
			parenthesis--;
		}
		index++;
	}
	return (index);
}
