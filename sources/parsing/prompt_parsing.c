/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/14 18:22:33 by antgabri         ###   ########.fr       */
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
	int	tmp;

	tmp = i;
	while (prompt[i] != delimiter)
	{
		if (prompt[i] == '\0')
			return (FAILURE);
		i++;
	}
	if (i > tmp + 1)
		return (i);
	else
		return (tmp);
}

/***
*@brief Compte le nombre de mots dans la chaine 
de caractère en evitant de compter
les espaces entre les quotes et les quotes vides
*@return le nombre de mots
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
		if (prompt[i] == '\'' || prompt[i] == '\"')
			i = quote_delimiter(prompt, prompt[i], i + 1);
		else
		{
			while (prompt[i + 1] && ft_iswhitespace(prompt[i]) == false)
				i++;
		}
		if (i == -1)
			return (FAILURE);
		else if (i > start + 1)
			nb_words++;
	}
	return (nb_words);
}
