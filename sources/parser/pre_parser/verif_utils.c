/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/11 14:23:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"

static int	print_error_arg(t_error *errors, const char *token)
{
	errno = ESYNTAX;
	perror_switch(errors, "kikishell", token);
	return (FAILURE);
}

int	verif_if_quote_closed(const char *prompt, t_error *errors)
{
	int		i;
	bool	quote;
	char	quote_type;

	quote_type = 0;
	i = 0;
	quote = false;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true && quote == false)
		{
			quote_type = prompt[i];
			quote = true;
		}
		else if (prompt[i] == quote_type && quote == true)
			quote = false;
		i++;
	}
	if (quote == true)
		return (print_error_arg(errors, &quote_type));
	return (SUCCESS);
}

int	verif_if_parenthesis_closed(const char *prompt, t_error *errors)
{
	int	i;
	int	index_parenthesis;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	index_parenthesis = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		else if (prompt[i] == '(')
		{
			index_parenthesis = i;
			parenthesis++;
		}
		else if (prompt[i] == ')')
		{
			index_parenthesis = i;
			parenthesis--;
		}
		if (prompt[i] != '\0')
			i++;
	}
	if (parenthesis != 0)
		return (print_error_arg(errors, &prompt[index_parenthesis]));
	return (SUCCESS);
}

int	verif_token_separation(const char *prompt, t_error *errors)
{
	int		i;
	int		tmp;
	char	token;

	i = 0;
	if (verif_before_operator(prompt, &token) == FAILURE)
		return (print_error_arg(errors, &token));
	while (prompt[i])
	{
		if (is_operator(prompt + i) == true || is_pipe(prompt + i) == true)
		{
			tmp = i;
			token = prompt[i];
			i = place_cursor_after_token(prompt, i);
			if (i - tmp > 2)
				return (print_error_arg(errors, &token));
			i = ft_skip_whitespaces(prompt, i);
			if (is_operator(prompt + i) == true
				|| is_pipe(prompt + i) == true
				|| prompt[i] == '\0')
				return (print_error_arg(errors, &token));
		}
		i++;
	}
	return (SUCCESS);
}

int	verif_arg_parenthesis(const char *prompt, t_error *errors)
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
				print_error_arg(errors, &(prompt[i]));
				return (FAILURE);
			}
		}
		if (prompt[i])
			i++;
	}
	return (SUCCESS);
}
