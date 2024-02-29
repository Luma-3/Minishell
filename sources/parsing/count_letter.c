/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_letter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:30:38 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/29 17:21:04 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Verifie si les quotes du debut se ferment bien dans la suite de 
 * la chaine
*/
static int	count_quote_around_word(const char *prompt, char delimiter, int i)
{
	while (prompt[i] && prompt[i] != delimiter)
	{
		i++;
	}
	if (prompt[i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Compte le nombre de lettres entre les quotes
*/
static int	count_letter_between_quote(const char *prompt,
	char delimiter, int i)
{
	int	nb_letters;

	nb_letters = 0;
	while (prompt[i] && prompt[i] != delimiter)
	{
		nb_letters++;
		i++;
	}
	return (nb_letters);
}

/**
 * @brief Compte le nombre de lettres dans un mot qui n'a pas de quotes
*/
static int	count_word_letter(const char *prompt, int i)
{
	int		nb_letters;
	char	quote_type;

	nb_letters = 0;
	quote_type = 0;
	while (prompt[i] != '\0' && ft_iswhitespace(prompt[i]) == false)
	{
		if (isquote_type(prompt[i]) == true && verif_quote_delimiter(prompt, prompt[i], i + 1) == SUCCESS)
		{
			quote_type = prompt[i];
			i++;
			while (prompt[i] != quote_type)
			{
				nb_letters++;
				i++;
			}
		}
		nb_letters++;
		i++;
	}
	return (nb_letters);
}

/**
 * @brief Regarde la premier lettre de la chaine de 
 * caractère et envoie dans la bonne fonction pour compter les lettres
*/
int	count_letters(const char *prompt, int i)
{
	while (ft_iswhitespace(prompt[i]) == true)
		i++;
	if (isquote_type(prompt[i]) == true)
	{
		if (count_quote_around_word(prompt, prompt[i], i + 1) == FAILURE)
			return (FAILURE);
		return (count_letter_between_quote(prompt, prompt[i], i + 1));
	}
	else
		return (count_word_letter(prompt, i));
}
