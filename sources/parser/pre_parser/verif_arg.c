/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/21 09:30:04 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static void	print_error_arg(char token)
{
	ft_putstr_fd("parse error near '", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static int	verif_if_quote_closed(const char *prompt)
{
	int		i;
	bool	quote;
	char	quote_type;

	quote_type = 0;
	i = 0;
	quote = false;
	while (prompt[i])
	{
		if ((prompt[i] == '\"' && quote == false)
			|| (prompt[i] == '\'' && quote == false))
		{
			quote_type = prompt[i];
			quote = true;
		}
		else if (prompt[i] == quote_type && quote == true)
			quote = false;
		i++;
	}
	if (quote == true)
		return (print_error_arg(quote_type), FAILURE);
	return (SUCCESS);
}

static int	verif_if_parenthesis_closed(const char *prompt)
{
	int	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		else if (prompt[i] == '(')
			parenthesis++;
		else if (prompt[i] == ')')
			parenthesis--;
		i++;
	}
	if (parenthesis != 0)
		return (print_error_arg('('), FAILURE);
	return (SUCCESS);
}

static int	verif_token_separation(const char *prompt)
{
	int		i;
	int		tmp;
	char	token;

	i = 0;
	while (prompt[i])
	{
		if (is_operator(prompt + i) == true || is_pipe(prompt + i) == true)
		{
			token = prompt[i];
			tmp = i;
			i = place_cursor_after_token(prompt, i);
			if (i - tmp > 2)
				return (print_error_arg(token), FAILURE);
			i = ft_skip_whitespaces(prompt, i);
			if (is_operator(prompt + i) == true
				|| is_pipe(prompt + i) == true || prompt[i] == '\0')
				return (print_error_arg(token), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	verif_arg(const char *prompt)
{
	if (verif_if_quote_closed(prompt) == FAILURE)
		return (FAILURE);
	else if (verif_if_parenthesis_closed(prompt) == FAILURE)
		return (FAILURE);
	else if (verif_token_separation(prompt) == FAILURE)
		return (FAILURE);
	else
		return (SUCCESS);
}
