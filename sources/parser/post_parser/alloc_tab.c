/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/27 16:27:33 by antgabri         ###   ########.fr       */
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

char	**alloc_tab(char *prompt)
{
	char	**tab;
	int		nb_words;
	t_list	*args_lst;

	args_lst = split_arg(prompt);
	if (args_lst == NULL)
		return (NULL);
	
	return (tab);
}


			// tab[index] = clean_quote(tab[index]);
			// if (tab[index] == NULL)
			// 	return (ft_rm_split(tab), NULL);