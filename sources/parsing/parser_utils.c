/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:42:27 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/15 16:52:58 by jbrousse         ###   ########.fr       */
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
