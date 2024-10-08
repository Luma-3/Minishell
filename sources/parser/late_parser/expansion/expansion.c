/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:35:19 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 15:45:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	cmp_lst(void *a, void *b)
{
	char	lower_a;
	char	lower_b;

	while (*(char *)a && *(char *)b)
	{
		lower_a = ft_tolower(*(char *)a);
		lower_b = ft_tolower(*(char *)b);
		if (lower_a != lower_b)
			return (lower_a - lower_b);
		a++;
		b++;
	}
	return (0);
}

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

static void	first_expansions(t_core *core_data, t_list *indexer)
{
	if (ft_strchr((const char *)indexer->content, '~') != NULL)
		indexer->content = (void *)handle_tilde(indexer->content,
				core_data->uname);
	if (ft_strchr((const char *)indexer->content, '$') != NULL)
		indexer->content = (void *)handle_env(core_data, indexer->content);
}

int	expansion_cmd(t_core *core_data, t_list **args)
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
				if (match_files == NULL)
					return (FAILURE);
				ft_lstsort(&match_files, &cmp_lst);
				indexer = match_files;
				connect_list(index_prev, match_files, args);
			}
		}
		index_prev = indexer;
		indexer = indexer->next;
	}
	return (SUCCESS);
}
