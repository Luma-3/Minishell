/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_copy_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:19:34 by anthony           #+#    #+#             */
/*   Updated: 2024/02/22 18:01:25 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_tab(char **temp)
{
	int		i;
	int		len;
	char	**new_tab;

	len = 0;
	i = 0;
	while (temp[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (new_tab == NULL)
		return (NULL);
	while (temp[i])
	{
		new_tab[i] = ft_strdup(temp[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static char	*ft_copy_until_token(char *tab, char *token, int i)
{
	int		j;
	char	*temp;

	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(tab) + 1));
	if (temp == NULL)
		return (NULL);
	while (ft_iswhitespace(tab[i]) == true || tab[i] == token[0])
		i++;
	while (tab[i] && tab[i] != token[0])
	{
		temp[j] = tab[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

char	**ft_copy_tab_split(char **tab, int i)
{
	int		j;
	int		k;
	int		nb_token;
	char	**new_tab;
	int		pos_after_token;

	j = 0;
	k = 0;
	pos_after_token = 0;
	nb_token = ft_search_token(tab[i], "&&");
	new_tab = malloc(sizeof(char *) * (ft_strlen(tab[i]) + nb_token + 1));
	if (new_tab == NULL)
		return (NULL);
	while (tab[j])
	{
		new_tab[k] = ft_strdup(tab[j]);
		if (j == i)
		{
			while (k < j + nb_token + 1)
			{
				new_tab[k] = ft_strdup(ft_copy_until_token(tab[i], "&&", pos_after_token));
				pos_after_token = pos_after_token + ft_strlen(new_tab[k]) + 2;
				k++;
			}
			j++;
		}
		else
		{
			j++;
			k++;
		}
	}
	new_tab[k] = NULL;
	// free(tab);
	return (new_tab);
}
