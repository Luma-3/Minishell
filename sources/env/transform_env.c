/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:52:52 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 17:59:50 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_list	*copy_env(char **envp)
{
	int		i;
	t_list	*head_env_list;

	i = -1;
	head_env_list = NULL;
	while (envp[++i])
	{
		ft_lstadd_back(&head_env_list, ft_lstnew(ft_strdup(envp[i])));
	}
	return (head_env_list);
}

static void	free_tab(char **tab, int index)
{
	while (index >= 0)
	{
		index--;
		free(tab[index]);
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
			return (NULL);
		}
		env[i] = ft_strdup(env_lst->content);
		env_lst = env_lst->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
