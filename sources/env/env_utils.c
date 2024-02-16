/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:09:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 17:33:56 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ms_getenv(t_list *env, const char *name)
{
	char	*format_name;
	int		name_len;

	format_name = ft_strjoin(name, "=");
	name_len = ft_strlen(format_name);
	if (!format_name)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->content, format_name, name_len) == 0)
		{
			free(format_name);
			return (ft_strdup(env->content + name_len));
		}
		env = env->next;
	}
	free(format_name);
	return (NULL);
}

int	ms_setenv(t_list *env, const char *name, const char *value)
{
	char	*format_name;
	t_list	*new_var;

	format_name = ft_strjoin(name, "=");
	while (env)
	{
		if (ft_strncmp(env->content, format_name, ft_strlen(format_name)) == 0)
		{
			free(env->content);
			env->content = ft_strjoin(format_name, value);
			free(format_name);
			return (SUCCESS);
		}
		env = env->next;
	}
	new_var = ft_lstnew(ft_strjoin(format_name, value));
	if (!new_var)
		return (FAILURE);
	ft_lstadd_back(&env, new_var);
	free(format_name);
	return (FAILURE);
}
