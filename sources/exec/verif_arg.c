/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/22 14:28:02 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_token(char *prompt, char token)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == token)
		{
			while (prompt[i] == token)
				i++;
			if (prompt[i + 1] == '\0')
				return (FAILURE);
			while (ft_iswhitespace(prompt[i]) == true)
			{
				if (prompt[i + 1] == '\0')
					return (FAILURE);
				i++;
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	verif_arg(char *prompt)
{
	if (ft_strchr(prompt, '|') != 0
		&& verif_token(prompt, '|') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '&') != 0
		&& verif_token(prompt, '&') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '>') != 0
		&& verif_token(prompt, '>') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '>') != 0
		&& verif_token(prompt, '>') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '<') != 0
		&& verif_token(prompt, '<') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '<') != 0
		&& verif_token(prompt, '<') == FAILURE)
		return (print_error_message(), FAILURE);
	if (ft_strchr(prompt, '|') != 0
		&& verif_token(prompt, '|') == FAILURE)
		return (print_error_message(), FAILURE);
	return (SUCCESS);
}
