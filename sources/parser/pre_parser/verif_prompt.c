/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:43:42 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 13:14:46 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	verif_prompt(const char *prompt)
{
	if (verif_arg_parenthesis(prompt) == FAILURE)
		return (FAILURE);
	else if (verif_if_quote_closed(prompt) == FAILURE)
		return (FAILURE);
	else if (verif_if_parenthesis_closed(prompt) == FAILURE)
		return (FAILURE);
	else if (verif_token_separation(prompt) == FAILURE)
		return (FAILURE);
	else
		return (SUCCESS);
}
