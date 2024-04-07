/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 17:37:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

long	count_letters(const char *start_word)
{
	int	i;

	i = 0;
	while (start_word[i])
	{
		if (ft_iswhitespace(start_word[i]) == true)
			break ;
		else if (is_quote(start_word[i]) == true)
			i = place_cursor_quote(start_word, i) + 1;
		else
			i++;
	}
	return (i);
}
