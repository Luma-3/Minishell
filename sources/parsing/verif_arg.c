/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:12 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/06 11:41:50 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	verif_if_quote_closed(char *prompt)
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

static int	verif_if_parenthesis_closed(char *prompt)
{
	int	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (prompt[i])
	{
		if (isquote_type(prompt[i]) == true)
			i = place_cursor_after_quote(prompt, i);
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

static int	verif_token_separation(char *prompt)
{
	int		i;
	char	token;

	token = 0;
	i = 0;
	while (prompt[i])
	{
		if (is_token(prompt[i]) == true)
		{
			token = prompt[i];
			if (is_token(prompt[i + 1]) == true && prompt[i] != prompt[i + 1])
				return (print_error_arg(token), FAILURE);
			else if (is_token(prompt[i + 1]) == true
				&& prompt[i] == prompt[i + 1])
				i += 2;
			else if (prompt[i] == '|')
				i++;
			i = ft_skip_whitespaces(prompt, i);
			if (is_token(prompt[i]) == true || prompt[i] == '\0')
				return (print_error_arg(token), FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	verif_arg(char *prompt)
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
