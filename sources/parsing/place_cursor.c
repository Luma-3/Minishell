/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:23 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/15 12:04:00 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
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
			if (prompt[i] == '\'' || prompt[i] == '\"')
				return (i);
		}
	}
	return (i + 1);
}
