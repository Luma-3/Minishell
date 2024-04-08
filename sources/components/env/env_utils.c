/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:09:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/08 17:51:24 by jbrousse         ###   ########.fr       */
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

int	ms_setenv(t_list **env, const char *name, const char *value)
{
	char	*format_name;
	char	*new_content;
	t_list	*new_var;
	t_list	*tmp;

	format_name = ft_strjoin(name, "=");
	if (!format_name)
		return (FAILURE);
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, format_name, ft_strlen(format_name)) == 0)
		{
			free(tmp->content);
			if (!value || !*value)
				tmp->content = ft_strdup(format_name);
			else
				tmp->content = ft_strjoin(format_name, value);
			free(format_name);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	new_content = ft_strjoin(format_name, value);
	free(format_name);
	if (!new_content)
		return (FAILURE);
	new_var = ft_lstnew(new_content);
	if (!new_var)
	{
		free(new_content);
		return (errno = ENOMEM, FAILURE);
	}
	ft_lstadd_front(env, new_var);
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
