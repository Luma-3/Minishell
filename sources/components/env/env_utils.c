/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:09:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 13:19:12 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

char	*ms_getenv(t_list *env, const char *name)
{
	char	*format_name;
	size_t	name_len;

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

static t_list	*find_var(t_list **env, const char *name)
{
	t_list	*iterator;

	iterator = *env;
	while (iterator)
	{
		if (strncmp(iterator->content, name, strlen(name)) == 0)
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

int	ms_setenv(t_list **env, const char *name, const char *value)
{
	char	*format_name;
	char	*new_content;
	t_list	*node_var;

	format_name = ft_strjoin(name, "=");
	if (!format_name)
		return (FAILURE);
	new_content = ft_strjoin(format_name, value);
	if (!new_content)
		return (free(format_name), FAILURE);
	node_var = find_var(env, format_name);
	free(format_name);
	if (node_var)
	{
		node_var->content = new_content;
	}
	else
	{
		node_var = ft_lstnew(new_content);
		if (!node_var)
			return (free(new_content), FAILURE);
		ft_lstadd_front(env, node_var);
	}
	return (SUCCESS);
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
