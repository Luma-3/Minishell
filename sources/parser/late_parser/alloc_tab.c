/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/06 17:54:26 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

char	**list_to_tab(t_list **lst)
{
	t_list	*indexer;
	char	**tab;
	char	*tmp_data;
	int		i;

	i = 0;
	tab = ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	indexer = *lst;
	while (indexer)
	{
		tmp_data = (char *)indexer->content;
		tab[i] = clean_quote(tmp_data);
		if (tab[i] == NULL)
		{
			ft_rm_split(tab);
			return (NULL);
		}
		indexer = indexer->next;
		i++;
	}
	ft_lstclear(lst, free);
	tab[i] = NULL;
	return (tab);
}
