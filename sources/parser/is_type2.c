/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:00:57 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 19:08:12 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_subshell(const char *cmd, int size_cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && i < size_cmd)
	{
		if (cmd[i] == '(')
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
		i++;
	}
	if (have_pipe > 0)
		return (true);
	return (false);
}
