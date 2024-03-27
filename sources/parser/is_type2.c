/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:00:57 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 17:10:23 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_subshell(const char *cmd, int size_cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && i < size_cmd)
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
