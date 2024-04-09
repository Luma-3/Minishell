/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 17:37:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

extern volatile int	g_sigreceiver;

static int	find_all_files(t_dstack *stack, t_match_file *match_file,
	t_list **lst, int i)
{
	DIR				*dir;
	t_list			*tmp;

	if (match_file == NULL || match_file->path == NULL)
		return (FAILURE);
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
	free(match_file->old_data);
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
	if (stack->top != NULL && g_sigreceiver == 0)
	{
		rec_all(stack, list);
	}
}

void	free_match_file(t_match_file *match_file)
{
	if (match_file->path != NULL)
		free(match_file->path);
	if (match_file->prefix != NULL)
		free(match_file->prefix);
	if (match_file->suffix != NULL)
		free(match_file->suffix);
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
			break ;
		if (data[i] != '\0')
			i++;
	}
	init_match_file(&match_file, data, i);
	if (access(match_file.path, F_OK) == FAILURE)
		return (no_access_file(stack, list, &match_file));
	if (g_sigreceiver == SIGINT)
		return (free_match_file(&match_file));
	call_recursion(&match_file, stack, list, i);
	free_match_file(&match_file);
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
		return (free(tmp), NULL);
	if (d_push_stk(stack, tmp->content) == FAILURE)
	{
		ft_lstadd_front(&new_head, tmp);
		return (free(start_content), new_head);
	}
	rec_all(stack, &new_head);
	d_clear_stk(stack, free);
	free(stack);
	clean_access_lst(&new_head, start_content);
	free(tmp);
	return (new_head);
}
