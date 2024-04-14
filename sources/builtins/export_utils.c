/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:40:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 13:21:53 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "parser.h"

bool	is_valid_name(char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (i == 0 && ft_isdigit(name[i]))
			return (false);
		if (valid_env_char(name[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

char	*get_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup(arg));
	return (ft_substr(arg, 0, i));
}

char	*get_value(char *arg)
{
	char	*value;
	char	*start_value;

	start_value = ft_strchr(arg, '=');
	if (start_value == NULL)
		return (NULL);
	value = ft_strndup(start_value + 1, ft_strlen(start_value));
	return (value);
}
