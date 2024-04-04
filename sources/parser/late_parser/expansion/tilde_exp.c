/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:10:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/04 18:16:24 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

bool	check_tilde(const char *arg, const int prev_i, const int next_i)
{
	if (ft_iswhitespace(arg[next_i]) == true || arg[next_i] == '\0'
		|| arg[next_i] == '/')
	{
		if (prev_i < 0 || ft_iswhitespace(arg[prev_i]) == true
			|| arg[prev_i] == '\0')
			return (true);
	}
	return (false);
}

char	*copy_data_tilde(const char *uname, char *arg, int index)
{
	char	*home;
	char	*new_arg;

	home = get_home(uname);
	if (home == NULL)
		return (arg);
	new_arg = ft_insert_str(arg, home, "~", index);
	free(arg);
	return (new_arg);
}

char	*handle_tilde(const char *arg, const char *uname)
{
	int		i;
	char	*new_arg;

	i = 0;
	new_arg = (char *)arg;
	while (new_arg[i])
	{
		i = skip_quote_parenthesis(new_arg, i);
		if (new_arg[i] == '~' && check_tilde(new_arg, i - 1, i + 1) == true)
		{
			new_arg = copy_data_tilde(uname, new_arg, i);
		}
		if (new_arg[i] != '\0')
			i++;
	}
	return (new_arg);
}
