/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:35:19 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 18:57:52 by jbrousse         ###   ########.fr       */
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

static t_list	*handle_all(const char *arg)
{
	t_list	*match_files;
	int		i;

	i = 0;
	match_files = NULL;
	while (arg[i])
	{
		i = skip_quote_parenthesis(arg, i);
		if (arg[i] == '*')
		{
			match_files = get_all_file((char *)arg);
			break ;
		}
		i++;
	}
	return (match_files);
}

void	connect_list(t_list *indexer, t_list *index_prev, t_list *match_files, t_list **args)
{
	t_list	*tmp;

	tmp = indexer->next;
	if (index_prev == NULL)
		*args = match_files;
	else
		index_prev->next = match_files;
	ft_lstdelone(args, indexer, free);
	while (match_files->next)
		match_files = match_files->next;
	match_files->next = tmp;
}

int	expansion_cmd(t_maindata *core_data, t_list **args)
{
	t_list	*indexer;
	t_list	*match_files;
	t_list	*index_prev;

	indexer = *args;
	index_prev = NULL;
	while (indexer)
	{
		if (ft_strchr((const char *)indexer->content, '~') != NULL)
			indexer->content = (void *)handle_tilde(indexer->content, core_data->uname);
		if (ft_strchr((const char *)indexer->content, '$') != NULL)
			indexer->content = (void *)handle_env(core_data, indexer->content);
		if (ft_strchr((const char *)indexer->content, '*') != NULL)
		{
			
			match_files = handle_all(indexer->content);
			if (match_files != NULL)
			{
				connect_list(indexer, index_prev, match_files, args);
				indexer = match_files;
			}
		}
		index_prev = indexer;
		indexer = indexer->next;
	}
	return (SUCCESS);
}
