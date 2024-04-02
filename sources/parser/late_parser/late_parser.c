/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:46:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 16:03:26 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list	*split_arg(const char *prompt)
{
	t_list	*args_lst;
	int		len;
	int		i;

	i = 0;
	args_lst = NULL;
	while (prompt[i])
	{
		i = ft_skip_whitespaces(prompt, i);
		len = count_letters(&prompt[i]);
		if (len != 0)
		{
			ft_lstadd_back(&args_lst,
				ft_lstnew(ft_strndup(&prompt[i], len)));
			i += len;
		}
	}
	return (args_lst);
}

char	**late_parser(t_maindata *core_data, t_ats *node)
{
	t_list	*lst_args;
	char	**tab_args;

	tab_args = NULL;
	lst_args = split_arg(node->data->cmd);
	if (lst_args == NULL)
		return (NULL);
	expansion_cmd(core_data, &lst_args);
	tab_args = list_to_tab(&lst_args);
	return (tab_args);
}
