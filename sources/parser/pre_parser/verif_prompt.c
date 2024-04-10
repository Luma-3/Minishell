/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:43:42 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:25:30 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	verif_prompt(const char *prompt, t_error *errors)
{
	if (verif_if_parenthesis_closed(prompt, errors) == FAILURE)
		return (FAILURE);
	else if (verif_arg_parenthesis(prompt, errors) == FAILURE)
		return (FAILURE);
	else if (verif_if_quote_closed(prompt, errors) == FAILURE)
		return (FAILURE);
	else if (verif_token_separation(prompt, errors) == FAILURE)
		return (FAILURE);
	else
		return (SUCCESS);
}
