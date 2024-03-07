/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:52:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 11:55:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_parenthesis(const char token)
{
	if (token == '(' || token == ')')
	{
		return (true);
	}
	return (false);
}

int	is_pipe(const char *prompt, int index)
{
	if (prompt[index] == '|' && prompt[index + 1] != '|')
	{
		return (true);
	}
	return (false);
}

int	is_token(char token)
{
	if (token == '|' || token == '&')
	{
		return (true);
	}
	return (false);
}

int	is_quote_type(char c)
{
	if (c == '\'' || c == '\"')
	{
		return (true);
	}
	return (false);
}

int	is_redir_type(const char *prompt, int index)
{
	if (prompt[index] == '<' && prompt[index + 1] != '<')
		return (REDIR_IN);
	else if (prompt[index] == '>' && prompt[index + 1] != '>')
		return (REDIR_OUT);
	else if (prompt[index] == '>' && prompt[index + 1] == '>')
		return (REDIR_OUT_APPEND);
	else if (prompt[index] == '<' && prompt[index + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (0);
}
