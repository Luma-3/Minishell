/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:10:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 12:57:40 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

bool	check_tilde(const char *arg, const int prev_i, const int next_i)
{
	if (ft_iswhitespace(arg[next_i]) == true || arg[next_i] == '\0'
		|| arg[next_i] == '/')
	{
		if (prev_i < 0 || ft_iswhitespace(arg[prev_i]) == true || arg[prev_i] == '\0')
			return (true);
	}
	return (false);
}

char	*copy_data_tilde(const char *uname, char *arg, int index)
{
	char	*home;
	char 	*new_arg;

	home = get_home(uname);
	if (home == NULL)
		return (arg);
	new_arg = ft_insert_str(arg, home, "~", index);
	free(arg);
	return (new_arg);
}
