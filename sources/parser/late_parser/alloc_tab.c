/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/05 18:40:32 by jbrousse         ###   ########.fr       */
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
		i++;
		indexer = indexer->next;
	}
	ft_lstclear(lst, free);
	return (tab);
}
