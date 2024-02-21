/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/21 14:06:46 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_token(char *prompt, char token)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == token && prompt[i + 1] == '\0')
			return (FAILURE);
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
