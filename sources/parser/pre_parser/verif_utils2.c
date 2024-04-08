/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:43:18 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/08 16:29:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"

// static void	error_subshell(const char *prompt)
// {
// 	print_error_arg();
// 	while (*prompt
// 		&& *prompt != ')'
// 		&& is_operator(prompt) == false
// 		&& ft_iswhitespace(*prompt) == false
// 		&& is_pipe(prompt) == false)
// 	{
// 		ft_putchar_fd(*prompt, STDERR_FILENO);
// 		prompt++;
// 	}
// 	ft_putstr_fd("'\n", STDERR_FILENO);
// }


static int	verif_token_before(const char *prompt, int i)
{
	while (i >= 0)
	{
		if (ft_iswhitespace(prompt[i]) == true)
			i--;
		if (prompt[i] == '\0' || is_operator(prompt + i - 1) == true
			|| is_pipe(prompt + i) == true)
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
		if (is_quote(prompt[i]) == true)
			i = skip_quote_parenthesis(prompt, i);
		if (prompt[i] == '(')
		{
			if (verif_token_before(prompt, i - 1) == FAILURE)
			{
				print_error_arg(prompt[i]);
				return (FAILURE);
			}
		}
		if (prompt[i])
			i++;
	}
	return (SUCCESS);
}
