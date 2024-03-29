/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 18:59:12 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

static void	pop_stack_to_list(t_dstack *stack, t_list **list)
{
	char	*data;
	int		i;

	
	while (stack->top != NULL)
	{
		i = 0;
		data = (char *)stack->top->data;
		while (data[i] != '\0')
		{
			if (data[i] == '*')
				return ;
			i++;
		}
		ft_lstadd_back(list, ft_lstnew(d_pop_stk(stack)));
	}
}

static int	find_all_files(t_dstack *stack, t_match_file match_file, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*token;
	char			*new;
	char			*old_data;
	
	old_data = NULL;
	dir = opendir(match_file.path);
	if (dir == NULL)
	{
		return (FAILURE);
	}
	old_data = (char *)d_pop_stk(stack);
	token = get_token(match_file.prefix, match_file.suffix);
	if (token == NULL)
		return (FAILURE);
	while (true)
	{
		entry = readdir(dir);
		if (entry == NULL)
			return (SUCCESS);
		if (find_match_file(entry->d_name, match_file.prefix, match_file.suffix) == true)
		{
			new = ft_insert_str(old_data, entry->d_name, token, i);
			d_push_stk(stack, new);
		}
	}
	return (SUCCESS);
}

static void	call_recursion(t_match_file match_file, t_dstack *stack, t_list **list, int i)
{
	int len;

	len = 0;
	if (match_file.prefix != NULL)
	{
		len = ft_strlen(match_file.prefix);
	}
	if (find_all_files(stack, match_file, i - len) == FAILURE)
	{
		d_drop_stk(stack, free);
	}
	pop_stack_to_list(stack, list);
	if (stack->top != NULL)
	{
		rec_all(stack, list);
	}
}

void	rec_all(t_dstack *stack, t_list **list)
{
	t_match_file	match_file;
	char			*data;
	int				i;
	
	i = 0;
	data = (char *)stack->top->data;
	while (data[i])
	{
		i = skip_quote_parenthesis(data, i);
		if (data[i] == '*')
		{
			match_file.path = get_path_wildcard(data, i);
			match_file.prefix = get_prefix(data, i);
			match_file.suffix = get_suffix(data, i);
			break ;
		}
		if (data[i] != '\0')
			i++;
	}
	call_recursion(match_file, stack, list, i);
}

t_list	*get_all_file(char *arg)
{
	t_dstack	*stack;
	t_list		*list;

	list = NULL;
	stack = d_init_stk();
	if (stack == NULL)
		return (NULL);
	d_push_stk(stack, arg);
	rec_all(stack, &list);
	return (list);
}
