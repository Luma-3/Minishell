/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:43:18 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/15 12:12:31 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"

int	verif_token_before(const char *prompt, int i)
{
	while (i >= 0)
	{
		if (ft_iswhitespace(prompt[i]) == true)
			i--;
		if (prompt[i] == '\0'
			|| (i - 1 >= 0 && is_operator(prompt + i - 1) == true)
			|| is_pipe(prompt + i) == true
			|| prompt[i] == '(')
			return (SUCCESS);
		else
		{
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	verif_token_after(const char *prompt, int i)
{
	i = ft_skip_whitespaces(prompt, i);
	if (is_operator(prompt + i) == true || is_pipe(prompt + i) == true
		|| prompt[i] == '\0' || is_redir_type(prompt + i) > 0)
		return (SUCCESS);
	return (FAILURE);
}

int	verif_before_operator(const char *prompt, char *token)
{
	int		i;
	int		nb_space;

	i = 0;
	nb_space = 0;
	while (prompt[i])
	{
		if (ft_iswhitespace(prompt[i]) == true)
			nb_space++;
		if (is_operator(prompt + i) == true || is_pipe(prompt + i) == true)
		{
			if ((nb_space == i && i - 1 != 0) || i - 1 == -1)
			{
				*token = prompt[i];
				return (FAILURE);
			}
			break ;
		}
		i++;
	}
	return (SUCCESS);
}
