/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:35:00 by anthony           #+#    #+#             */
/*   Updated: 2024/04/04 17:35:37 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_parenthesis(char parenthesis)
{
	if (parenthesis == '(')
		return (1);
	else
		return (-1);
}

char	check_quote(char quote, char c)
{
	if (quote == '\0')
		return (c);
	else
		return ('\0');
}
