/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:52:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 15:08:32 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_pipe(const char *prompt)
{
	if (prompt[0] == '|' && prompt[1] != '|')
	{
		return (true);
	}
	return (false);
}

int	is_operator(const char *token)
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

int	is_quote(const char c)
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
