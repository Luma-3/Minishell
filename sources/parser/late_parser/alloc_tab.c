/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/28 12:55:16 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"



// char	**alloc_tab(t_maindata *core_data, char *prompt)
// {
// 	char	**tab;
// 	t_list	*args_lst;

// 	tab = NULL;
// 	args_lst = split_arg(prompt);
// 	if (args_lst == NULL)
// 		return (NULL);
// 	expansion_cmd(core_data, args_lst);
// 	return (tab);
// }


			// tab[index] = clean_quote(tab[index]);
			// if (tab[index] == NULL)
			// 	return (ft_rm_split(tab), NULL);