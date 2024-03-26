/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/26 13:15:37 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"


int	verif_if_quote_closed(const char *prompt)
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
		return (print_error_arg(quote_type), FAILURE);
	return (SUCCESS);
}

int	verif_if_parenthesis_closed(const char *prompt)
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

int	verif_token_separation(const char *prompt)
{
	int		i;
	int		tmp;
	char	token;

	i = 0;
	if (verif_before_operator(prompt, &token) == FAILURE)
		return (print_error_arg(token), FAILURE);
	while (prompt[i])
	{
		if (is_operator(prompt + i) == true || is_pipe(prompt + i) == true)
		{
			tmp = i;
			token = prompt[i];
			i = place_cursor_after_token(prompt, i);
			if (i - tmp > 2)
				return (print_error_arg(token), FAILURE);
			i = ft_skip_whitespaces(prompt, i);
			if (is_operator(prompt + i) == true
				|| is_pipe(prompt + i) == true
				|| prompt[i] == '\0')
				return (print_error_arg(token), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
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
