/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:33:39 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/12 19:17:54 by jbrousse         ###   ########.fr       */
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
	while (prompt[i] != delimiter
		|| (prompt[i] == delimiter && ft_iswhitespace(prompt[i + 1]))
		|| (prompt[i] == delimiter && prompt[i + 1] != '\0'))
	{
		if (prompt[i] == '\0')
			return (FAILURE);
		i++;
		printf("del\n");
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
		while (ft_iswhitespace(prompt[i]) == true)
			i++;
		if (prompt[i] == '\'')
			i = quote_delimiter(prompt, '\'', i + 1);
		else if (prompt[i] == '\"')
			i = quote_delimiter(prompt, '\"', i + 1);
		else
		{
			while (ft_iswhitespace(prompt[i]) == false && prompt[i])
				i++;
		}
		if (i == -1)
			return (FAILURE);
		nb_words++;
		printf("%d\n", i);
		i++;
	}
	return (nb_words);
}
