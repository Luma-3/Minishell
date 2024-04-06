/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:35:19 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 12:11:35 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static t_list	*handle_all(t_list **lst, t_list *current_index)
{
	t_list	*match_files;
	char	*arg;
	int		i;

	i = 0;
	match_files = NULL;
	arg = (char *)current_index->content;
	while (arg[i])
	{
		i = skip_quote_parenthesis(arg, i);
		if (arg[i] == '*')
		{
			match_files = get_all_file(lst, current_index);
			break ;
		}
		if (arg[i] != '\0')
			i++;
	}
	return (match_files);
}

static void	connect_list(t_list *index_prev, t_list *match_files, t_list **args)
{
	t_list	*tmp;

	if (index_prev == NULL)
	{
		*args = match_files;
		return ;
	}
	tmp = index_prev->next;
	index_prev->next = match_files;
	ft_lstadd_back(&match_files, tmp);
}

static void	first_expansions(t_maindata *core_data, t_list *indexer)
{
	if (ft_strchr((const char *)indexer->content, '~') != NULL)
		indexer->content = (void *)handle_tilde(indexer->content,
				core_data->uname);
	if (ft_strchr((const char *)indexer->content, '$') != NULL)
		indexer->content = (void *)handle_env(core_data, indexer->content);
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
		if (indexer->content != NULL)
		{
			first_expansions(core_data, indexer);
			if (ft_strchr((const char *)indexer->content, '*') != NULL)
			{
				match_files = handle_all(args, indexer);
				if (match_files != NULL)
				{
					indexer = match_files;
					connect_list(index_prev, match_files, args);
				}
			}
		}
		index_prev = indexer;
		indexer = indexer->next;
	}
	return (SUCCESS);
}
