/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/15 17:22:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	trim_white_space(const char *const prompt)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_iswhitespace(prompt[i]) == true)
// 	{
// 		i++;
// 	}
// 	return (i);
// }

static int	quote_delimiter(const char *prompt, char delimiter, int i)
{
	while (prompt[i] != delimiter)
	{
		if (prompt[i] == '\0')
			return (FAILURE);
		i++;
	}
	return (i);
}

/**
 * @brief Compte le nombre de mots dans la chaine 
 * de caractère en evitant de compter
 * les espaces entre les quotes et les quotes vides
 * @return le nombre de mots
*/
int	count_words(const char *prompt)
{
	int	nb_words;
	int	i;
	int	start;

	i = -1;
	nb_words = 0;
	while (prompt[++i] != '\0')
	{
		start = i;
		while (ft_iswhitespace(prompt[i]) == true && prompt[i])
			i++;
		if (isquote_type(prompt[i]) == true)
		{
			i = quote_delimiter(prompt, prompt[i], i + 1);
			if (i > start + 1)
				nb_words++;
		}
		else
		{
			while (prompt[i + 1] && ft_iswhitespace(prompt[i]) == false)
				i++;
			nb_words++;
		}
	}
	return (nb_words);
}
