/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:07 by anthony           #+#    #+#             */
/*   Updated: 2024/02/23 19:22:51 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_token(char *tab, char *token)
{
	int	i;
	int	nb_token;

	i = 0;
	nb_token = 0;
	while (tab[i])
	{
		if (tab[i] == token[0] && tab[i + 1] == token[1])
		{
			nb_token++;
			i++;
		}
		i++;
	}
	return (nb_token);
}

int	is_there_token(char **tab, int i)
{
	while (tab[i])
	{
		if (ft_strnstr(tab[i], "&&", ft_strlen(tab[i])) != NULL)
			return (i);
		i++;
	}
	return (FAILURE);
}

char	**handle_token(char **tab, int i)
{
	char	**temp;
	int		pos;

	pos = 0;
	temp = ft_copy_tab(tab);
	while (tab[i])
	{
		if (ft_strnstr(tab[i], "&&", ft_strlen(tab[i])) != NULL)
		{
			free_tab_exec(temp);
			temp = ft_copy_tab_split(tab, i, pos);
			tab = ft_copy_tab(temp);
			i = 0;
		}
		i++;
	}
	free_tab_exec(temp);
	return (tab);
}
