/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 11:10:01 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int handle_env(const char *start_spec, t_list *envp)
{
	int		i;
	int		name_len;
	char	*name;
	char	*env_value;

	name_len = 0;
	while (start_spec[name_len] && start_spec[name_len] != ' ')
		name_len++;
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (name_len + 1);
	i = 0;
	while (start_spec[i] && start_spec[i] != ' ')
	{
		name[i] = start_spec[i];
		i++;
	}
	env_value = ms_getenv(envp, name);
	if (env_value)
	{
		ft_putstr_fd(env_value, 1);
	}
	free(name);
	return (name_len + 1);
}

int	is_printable_quote(const char *start_spec, bool *is_between_quotes, char *quote_type)
{	
	if (*start_spec == '\'' || *start_spec == '\"')
	{
		if (*is_between_quotes == false)
		{
			*is_between_quotes = true;
			*quote_type = *start_spec;
			return (false);
		}
		else if (*is_between_quotes == true && *quote_type == *start_spec)
		{
			*is_between_quotes = false;
			*quote_type = 0;
			return (false);
		}
		else if (*is_between_quotes == true)
			return (true);
	}
	return (true);
}
