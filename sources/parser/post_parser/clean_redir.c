/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:51:42 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/08 17:50:01 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	find_start_redir(const char *word)
{
	int	start_i;

	start_i = 0;
	while (word[start_i])
	{
		if (is_redir_type(word, start_i) > 0)
			break ;
		start_i++;
	}
	return (start_i);
}

static int	calcul_size_redir(const char *start_redir)
{
	int	i;

	i = 0;
	while (start_redir[i] && is_redir_type(start_redir, i) > 0)
		i++;
	i = ft_skip_whitespaces(start_redir, i);
	while (start_redir[i] && ft_iswhitespace(start_redir[i]) == false)
		i++;
	return (i);
}

char	*clean_redir(char *word)
{
	int		start_i;
	int		size_redir;
	char	*new_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_word = NULL;
	start_i = find_start_redir(word);
	size_redir = calcul_size_redir(&word[start_i]);
	new_word = ft_calloc(ft_strlen(word) - size_redir + 1, sizeof(char));
	if (new_word == NULL)
		return (NULL);
	while (word[i])
	{
		if (i == start_i)
			i += size_redir;
		else
			new_word[j++] = word[i++];
	}
	free(word);
	if (ft_strchr(new_word, '>') != NULL || ft_strchr(new_word, '<') != NULL)
		return (clean_redir(new_word));
	return (new_word);
}
