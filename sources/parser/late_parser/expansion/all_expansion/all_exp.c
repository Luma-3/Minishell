/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 10:26:18 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

static int	find_all_files(t_dstack *stack, t_match_file *match_file,
	t_list **lst, int i)
{
	DIR				*dir;
	t_list			*tmp;

	dir = opendir(match_file->path);
	if (dir == NULL)
		return (FAILURE);
	if (find_and_push(stack, match_file, dir, i) == false)
	{
		tmp = ft_lstnew(match_file->old_data);
		if (tmp != NULL)
			ft_lstadd_front(lst, tmp);
		closedir(dir);
		return (FAILURE);
	}
	if (closedir(dir) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static void	call_recursion(t_match_file *match_file, t_dstack *stack,
	t_list **list, int i)
{
	int	len;

	len = 0;
	if (match_file != NULL && match_file->prefix != NULL)
	{
		len = ft_strlen(match_file->prefix);
	}
	if (find_all_files(stack, match_file, list, i - len) == FAILURE)
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
	init_match_file(&match_file, data, i);
	while (data[i])
	{
		i = skip_quote_parenthesis(data, i);
		if (data[i] == '*')
		{
			init_match_file(&match_file, data, i);
			if (access(match_file.path, F_OK) == FAILURE)
				return (no_access_file(stack, list, &match_file));
			break ;
		}
		if (data[i] != '\0')
			i++;
	}
	call_recursion(&match_file, stack, list, i);
	(free(match_file.suffix), free(match_file.path));
	free(match_file.prefix);
}

t_list	*get_all_file(t_list **head, t_list *arg)
{
	t_dstack	*stack;
	t_list		*new_head;
	t_list		*tmp;
	char		*start_content;

	new_head = NULL;
	stack = d_init_stk();
	if (stack == NULL)
		return (NULL);
	tmp = ft_lstdetach(head, arg);
	start_content = ft_strdup(tmp->content);
	if (start_content == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if (d_push_stk(stack, tmp->content) == FAILURE)
	{
		ft_lstadd_front(&new_head, tmp);
		return (new_head);
	}
	free(tmp);
	rec_all(stack, &new_head);
	clean_access_lst(&new_head, start_content);
	return (new_head);
}
