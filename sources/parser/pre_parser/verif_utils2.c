/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:43:18 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/05 17:25:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"

static void	error_subshell(const char *prompt)
{
	print_error_arg_msg();
	while (*prompt
		&& *prompt != ')'
		&& *prompt != '\0'
		&& is_operator(prompt) == false
		&& ft_iswhitespace(*prompt) == false
		&& is_pipe(prompt) == false)
	{
		ft_putchar_fd(*prompt, STDERR_FILENO);
		prompt++;
	}
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static int	verif_token_before(const char *prompt, int i)
{
	while (i >= 0)
	{
		if (ft_iswhitespace(prompt[i]) == true)
			i--;
		if (is_operator(prompt + i - 1) == true
			|| is_quote(prompt[i]) == true
			|| prompt[i] == '\0')
			return (SUCCESS);
		else
		{
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	verif_arg_parenthesis(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '(')
		{
			if (verif_token_before(prompt, i - 1) == FAILURE)
			{
				error_subshell(prompt + i + 1);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
