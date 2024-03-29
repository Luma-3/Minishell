/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:35:19 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 16:19:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static char	*handle_tilde(const char *arg, const char *uname)
{
	int		i;
	char	*new_arg;

	i = 0;
	new_arg = (char *)arg;
	while (new_arg[i])
	{
		if (new_arg[i] == '~' && check_tilde(new_arg, i - 1, i + 1) == true)
		{
			new_arg = copy_data_tilde(uname, new_arg, i);
		}
		i++;
	}
	return (new_arg);
}

static char *handle_env(t_maindata *core_data, const char *arg)
{
	int	i;
	char	*new_arg;
	
	i = 0;
	new_arg = (char *)arg;
	while (new_arg[i])
	{
		if (new_arg[i] == '$' && (ft_iswhitespace(new_arg[i + 1]) == false || new_arg[i + 1] != '\0'))
		{
			new_arg = copy_data_env(core_data, new_arg, i);
		}
		i++;
	}
	return (new_arg);
}

static char	*handle_all(t_maindata *core_data, const char *arg)
{
	char	*new_arg;
	int		i;

	i = 0;
	new_arg = (char *)arg;
	while (new_arg[i])
	{
		i = skip_quote_parenthesis(new_arg, i);
		if (new_arg[i] == '*')
		{
			new_arg = find_data_all(core_data, new_arg, i);
		}
		i++;
	}
	return (NULL);
}

int	expansion_cmd(t_maindata *core_data, t_list const *args)
{
	t_list	*indexer;

	indexer = (t_list *)args;
	while (indexer)
	{
		if (ft_strchr((const char *)indexer->content, '~') != NULL)
			indexer->content = (void *)handle_tilde(indexer->content, core_data->uname);
		else if (ft_strchr((const char *)indexer->content, '$') != NULL)
		{
			indexer->content = (void *)handle_env(core_data, indexer->content);
		}
		else if (ft_strchr((const char *)indexer->content, '*') != NULL)
		{
			indexer->content = (void *)handle_all(core_data, indexer->content);
		}
		// if (ft_strchr ($))
		// 	handle_dollar();
		// if (ft_strchr(argv[i], '*'))
		// 	hanlde_all
		indexer = indexer->next;
	}
	return (SUCCESS);
}