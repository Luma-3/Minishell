/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:48:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/23 12:46:38 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static char	**insert_data(char **tab, const char *prompt, int nb_words)
{
	int	nb_letters;
	int	position;
	int	index;

	position = 0;
	index = 0;
	while (prompt[position] && index < nb_words)
	{
		position = ft_skip_whitespaces(prompt, position);
		nb_letters = count_letters(&prompt[position]);
		if (nb_letters != 0)
		{
			tab[index] = ft_strndup(&prompt[position], nb_letters);
			if (tab[index] == NULL)
				return (ft_rm_split(tab), NULL);
			tab[index] = clean_quote(tab[index]);
			if (tab[index] == NULL)
				return (ft_rm_split(tab), NULL);
			position += nb_letters;
			index++;
		}
	}
	return (tab);
}

char	**alloc_tab(char *prompt)
{
	char	**tab;
	int		nb_words;

	tab = NULL;
	nb_words = count_words(prompt);
	tab = (char **)ft_calloc(nb_words + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[nb_words] = NULL;
	return (insert_data(tab, prompt, nb_words));
}
