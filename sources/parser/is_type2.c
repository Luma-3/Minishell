/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:00:57 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 15:15:01 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_subshell(const char *cmd, int size_cmd)
{
	int	i;

	i = 0;
	while (i < size_cmd && cmd[i])
	{
		if (is_quote(cmd[i]) == true)
			i = place_cursor_quote(cmd, i);
		else if (cmd[i] == '(')
			return (true);
		else
			i++;
	}
	return (false);
}

bool	is_pipeline(const char *prompt)
{
	int	i;
	int	have_pipe;

	i = 0;
	have_pipe = 0;
	while (prompt[i])
	{
		if (is_pipe(prompt + i) == true)
			have_pipe++;
		if (is_operator(prompt + i) == true)
			return (false);
		i = skip_quote_parenthesis(prompt, i);
		if (prompt[i] == '\0')
			break ;
		i++;
	}
	if (have_pipe > 0)
		return (true);
	return (false);
}

bool	valid_env_char(const char c)
{
	if (ft_isalnum(c) == true || c == '_')
		return (true);
	return (false);
}
