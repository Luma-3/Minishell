/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:23 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/14 18:22:09 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
 * @brief Place le curseur sur le debut du prochain mot
 */
int	place_cursor(char *prompt, int i)
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
		}
	}
	return (i + 1);
}
