/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:52:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 23:56:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

static void	free_tab(char **tab, int index)
{
	while (index >= 0)
	{
		index--;
		free(tab + index);
	}
	free(tab);
}

char	**env_to_tab(t_list *env_lst)
{
	char	**env;
	int		i;

	env = (char **)ft_calloc(ft_lstsize(env_lst) + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (env_lst)
	{
		env[i] = (char *)ft_calloc(ft_strlen((char *)env_lst->content) + 1,
				sizeof(char));
		if (!env[i])
		{
			free_tab(env, i);
			free(env);
			return (NULL);
		}
		env[i] = ft_strdup(env_lst->content);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

t_list	*env_to_lst(char **envp)
{
	int		i;
	char	*tmp;
	t_list	*head_env_list;
	t_list	*new;

	i = -1;
	head_env_list = NULL;
	while (envp[++i])
	{
		tmp = ft_strdup(envp[i]);
		if (!tmp)
		{
			errno = ENOMEM;
			ft_lstclear(&head_env_list, free);
			return (NULL);
		}
		new = ft_lstnew(tmp);
		if (!new)
		{
			errno = ENOMEM;
			free(tmp);
			ft_lstclear(&head_env_list, free);
			return (NULL);
		}
		ft_lstadd_back(&head_env_list, new);
	}
	return (head_env_list);
}
