/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 18:18:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"
#include <dirent.h>

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
			{
				return ;
			}
			i++;
		}
		ft_lstadd_back(list, ft_lstnew(d_pop_stk(stack)));
	}
}

static int	find_all_files(t_dstack *stack, t_match_file *match_file, t_list **lst, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		stat_file;
	char			*token;
	char			*old_data;
	char			tmp[257];
	char			*suffix;
	char 			*path;
	bool			have_file;

	old_data = NULL;
	dir = opendir(match_file->path);
	if (dir == NULL)
		return (FAILURE);
	old_data = (char *)d_pop_stk(stack);
	if (match_file->suffix != NULL)
	{
		if (ft_strchr(match_file->suffix, '/') != 0)
			suffix = ft_strtrim(match_file->suffix, "/");
		else
			suffix = ft_strdup(match_file->suffix);
	}
	else
		suffix = ft_strdup(match_file->suffix);
	token = get_token(match_file->prefix, suffix);
	if (token == NULL)
		return (FAILURE);
	have_file = false;
	while (true)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		path = ft_strjoin(match_file->path, "/");
		path = ft_strjoin(path, entry->d_name);
		stat(path, &stat_file);
		ft_strlcpy(tmp, entry->d_name, 256);
		if (S_ISDIR(stat_file.st_mode))
		{
			ft_strlcat(tmp, "/", 257);
		}
		if (find_match_file(tmp, match_file->prefix,
				match_file->suffix) == true)
		{
			have_file = true;
			d_push_stk(stack, ft_insert_str(old_data, entry->d_name, token, i));
		}
	}
	if (have_file == false)
	{
		ft_lstadd_front(lst, ft_lstnew(old_data));
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	call_recursion(t_match_file *match_file, t_dstack *stack,
	t_list **list, int i)
{
	int	len;

	len = 0;
	if (match_file->prefix != NULL)
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
	while (data[i])
	{
		i = skip_quote_parenthesis(data, i);
		if (data[i] == '*')
		{
			match_file.suffix = get_suffix(data, i);
			match_file.path = get_path_wildcard(data, i);
			if (access(match_file.path, F_OK) == FAILURE)
			{
				ft_lstadd_front(list, ft_lstnew(d_pop_stk(stack)));
				return ;
			}
			match_file.prefix = get_prefix(data, i);
			break ;
		}
		if (data[i] != '\0')
			i++;
	}
	call_recursion(&match_file, stack, list, i);
}

static void clean_access_lst(t_list **head, char *start_content)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*free_node;

	tmp = *head;
	(void)start_content;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (access((char *)tmp->content, F_OK) == FAILURE)
		{
			free_node = ft_lstdetach(head, tmp);
			free(free_node->content);
			free(free_node);
		}
		tmp = next;
	}
	if (ft_lstsize(*head) == 0)
		ft_lstadd_front(head, ft_lstnew(start_content));
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
	d_push_stk(stack, tmp->content);
	free(tmp);
	rec_all(stack, &new_head);
	clean_access_lst(&new_head, start_content);
	return (new_head);
}
