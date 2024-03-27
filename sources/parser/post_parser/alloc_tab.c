/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/27 18:24:26 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

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

char	**alloc_tab(t_maindata *core_data, char *prompt)
{
	char	**tab;
	t_list	*args_lst;

	tab = NULL;
	args_lst = split_arg(prompt);
	if (args_lst == NULL)
		return (NULL);
	handle_wildcard(core_data, args_lst);
	return (tab);
}


			// tab[index] = clean_quote(tab[index]);
			// if (tab[index] == NULL)
			// 	return (ft_rm_split(tab), NULL);