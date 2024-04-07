/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:52:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 16:32:52 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_pipe(const char *prompt)
{
	if (prompt[0] == '|' && prompt[1] != '|')
	{
		return (true);
	}
	return (false);
}

bool	is_operator(const char *token)
{
	if (*token == '|' && *(token + 1) == '|')
	{
		return (true);
	}
	else if (*token == '&' && *(token + 1) == '&')
	{
		return (true);
	}
	return (false);
}

bool	is_quote(const char c)
{
	if (c == '\'' || c == '\"')
	{
		return (true);
	}
	return (false);
}

int	is_redir_type(const char *prompt)
{
	if (*prompt == '<' && *(prompt + 1) != '<')
		return (REDIR_IN);
	else if (*prompt == '>' && *(prompt + 1) != '>')
		return (REDIR_OUT);
	else if (*prompt == '>' && *(prompt + 1) == '>')
		return (REDIR_OUT_APPEND);
	else if (*prompt == '<' && *(prompt + 1) == '<')
		return (REDIR_HEREDOC);
	else
		return (0);
}
