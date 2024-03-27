/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:35:19 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 18:34:03 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static char	*copy_data_tilde(const char *uname, char *arg, int index)
{
	char	*home;
	char 	*new_arg;

	home = get_home(uname);
	if (home == NULL)
		return (arg);
	new_arg = ft_insert_str(arg, home, "~", index);
	return (new_arg);
}

static char *handle_tilde(const char *arg, const char *uname)
{
	int i;
	char *new_arg;

	i = 0;
	new_arg = (char *)arg;
	while (arg[i])
	{
		if (arg[i] == '~' && check_tilde(arg, i - 1 , i + 1) == true)
		{
			new_arg = copy_data_tilde(uname, (char *)arg, i);
		}
		i++;
	}
	return (new_arg);
}

int	handle_wildcard(t_maindata *core_data, t_list const *args)
{
	t_list	*indexer;

	indexer = (t_list *)args;
	while (indexer)
	{
		if (ft_strchr((const char *)indexer->content, '~') != NULL)
			indexer->content = (void *)handle_tilde(indexer->content, core_data->uname);
		else if (ft_strchr((const char *)indexer->content, '$') != NULL)
			indexer->content = (void *)handle_env(indexer->content, core_data->env);

		// if (ft_strchr ($))
		// 	handle_dollar();
		// if (ft_strchr(argv[i], '*'))
		// 	hanlde_all
		indexer = indexer->next;
	}
	return (SUCCESS);
}