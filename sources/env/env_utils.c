/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:09:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 20:06:20 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ms_getenv(t_list *env, const char *name)
{
	char	*format_name;
	int		name_len;

	format_name = ft_strjoin(name, "=");
	if (!format_name)
		return (NULL);
	name_len = ft_strlen(format_name);
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

int	ms_setenv(t_list **env, const char *name, const char *value)
{
	char	*format_name;
	t_list	*new_var;
	t_list	*tmp;

	format_name = ft_strjoin(name, "=");
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, format_name, ft_strlen(format_name)) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strjoin(format_name, value);
			free(format_name);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	new_var = ft_lstnew(ft_strjoin(format_name, value));
	if (!new_var)
		return (FAILURE);
	ft_lstadd_front(env, new_var);
	free(format_name);
	return (FAILURE);
}

int	ms_unsetenv(t_list **env, const char *name)
{
	char	*format_name;
	t_list	*tmp;

	format_name = ft_strjoin(name, "=");
	if (!format_name)
		return (FAILURE);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, format_name, ft_strlen(format_name)) == 0)
		{
			ft_lstdelone(env, tmp, free);
			free(format_name);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	free(format_name);
	return (FAILURE);
}
