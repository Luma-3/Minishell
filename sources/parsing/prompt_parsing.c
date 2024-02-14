/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/14 10:43:02 by antgabri         ###   ########.fr       */
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
/***
*@brief Vérifie si les quotes sont bien fermées
*/
static int	verify_quote(const char *prompt)
{
	int	nb_quote_left_side;
	int	nb_quote_right_side;
	int	i;

	i = 0;
	nb_quote_left_side = 0;
	nb_quote_right_side = 0;
	while (prompt[i] == '\'' || prompt[i] == '\"')
	{	
		nb_quote_left_side++;
		i++;
	}
	while (prompt[i] != '\'' && prompt[i] != '\"' && prompt[i])
		i++;
	while (prompt[i] == '\'' || prompt[i] == '\"')
	{	
		nb_quote_right_side++;
		i++;
	}
	if (nb_quote_left_side != nb_quote_right_side)
		return (FAILURE);
	return (0);
}

static int	count_quote(int nb_quote1, int nb_quote2)
{
	if ((nb_quote1 != 0 && nb_quote2 != 0 && nb_quote1 + nb_quote2 >= 4) 
		|| (nb_quote2 != 0 && nb_quote1 != 0 && nb_quote2 + nb_quote1 >= 4))
		return (2);
	return (0);
}

/***
*@brief Compte les lettres dans le prompt
*/
int	count_letters(const char *prompt)
{
	int	nb_letters;
	int	i;
	int	nb_quote1;
	int	nb_quote2;

	i = 0;
	nb_letters = 0;
	nb_quote1 = 0;
	nb_quote2 = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
			nb_quote1++;
		else if (prompt[i] == '\"')
			nb_quote2++;
		else if (prompt[i] != '\\')
			nb_letters++;
		i++;
	}
	if ((nb_quote1 != 0 && nb_quote1 % 2 != 0)
		|| (nb_quote2 != 0 && nb_quote2 % 2 != 0)
		|| verify_quote(prompt) == FAILURE)
		return (FAILURE);
	nb_letters += count_quote(nb_quote1, nb_quote2);
	return (nb_letters);
}

static int	quote_delimiter(const char *prompt, char delimiter, int i)
{
	while (prompt[i] != delimiter
		|| (prompt[i] == delimiter && ft_iswhitespace(prompt[i + 1]))
		|| (prompt[i] == delimiter && prompt[i + 1] != '\0'))
	{
		if (prompt[i] == '\0')
			return (FAILURE);
		i++;
	}
	return (i);
}

int	count_words(const char *prompt)
{
	int	nb_words;
	int	i;

	i = 0;
	nb_words = 0;
	while (prompt[i] != '\0')
	{
		while (prompt[i + 1] && ft_iswhitespace(prompt[i]) == true)
			i++;
		if (prompt[i] == '\'')
			i = quote_delimiter(prompt, '\'', i + 1);
		else if (prompt[i] == '\"')
			i = quote_delimiter(prompt, '\"', i + 1);
		else
		{
			while (prompt[i + 1] && ft_iswhitespace(prompt[i]) == false)
				i++;
		}
		if (i == -1)
			return (FAILURE);
		nb_words++;
		i++;
	}
	return (nb_words);
}
