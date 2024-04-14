/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:46:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 19:47:56 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list	*split_arg(const char *prompt)
{
	t_list	*args_lst;
	t_list	*new_node;
	long	len;
	int		i;
	char	*copy_prompt;

	i = 0;
	args_lst = NULL;
	while (prompt[i])
	{
		i = ft_skip_whitespaces(prompt, i);
		len = count_letters(&prompt[i]);
		if (len != 0)
		{
			copy_prompt = ft_strndup(&prompt[i], (size_t)len);
			if (copy_prompt == NULL)
				return (NULL);
			new_node = ft_lstnew(copy_prompt);
			if (new_node == NULL)
				return (ft_lstclear(&args_lst, free), NULL);
			ft_lstadd_back(&args_lst, new_node);
			i += len;
		}
	}
	return (args_lst);
}

static t_list	*split_arg_lst(t_list *args_lst)
{
	t_list	*new_lst;
	t_list	*tmp_lst;
	t_list	*tmp;

	new_lst = NULL;
	tmp = args_lst;
	while (tmp)
	{
		tmp_lst = split_arg((char *)tmp->content);
		ft_lstadd_back(&new_lst, tmp_lst);
		tmp = tmp->next;
	}
	return (new_lst);
}

char	**late_parser(t_maindata *core_data, t_ast *node)
{
	t_list	*lst_args;
	t_list	*lst_final;
	char	**tab_args;

	tab_args = NULL;
	lst_final = NULL;
	errno = 0;
	if (node->data->cmd == NULL)
		return (NULL);
	lst_args = split_arg(node->data->cmd);
	if (lst_args == NULL)
		return (NULL);
	if (expansion_cmd(core_data, &lst_args) == FAILURE)
		return (NULL);
	lst_final = split_arg_lst(lst_args);
	ft_lstclear(&lst_args, free);
	tab_args = list_to_tab(&lst_final);
	return (tab_args);
}
