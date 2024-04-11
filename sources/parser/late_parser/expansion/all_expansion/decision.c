/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:27:09 by anthony           #+#    #+#             */
/*   Updated: 2024/04/11 11:54:34 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

bool	decision_file(char *entry, char *suffix)
{
	int	len_suff;
	int	len_entry;

	len_suff = ft_strlen(suffix);
	len_entry = ft_strlen(entry);
	if ((ft_strncmp(entry + len_entry - len_suff,
				suffix, len_suff) == 0))
		return (true);
	return (false);
}

bool	decision_directory(char *entry, char *suffix_dir)
{
	int	len_suff_dir;
	int	len_entry;

	len_suff_dir = ft_strlen(suffix_dir);
	len_entry = ft_strlen(entry);
	if ((ft_strncmp(entry + len_entry - len_suff_dir,
				suffix_dir, len_suff_dir) == 0))
		return (true);
	return (false);
}

static bool	check_occurence(char *entry, char *to_find, int *i)
{
	*i = ft_findstr(entry, to_find, *i);
	if (*i == -1)
		return (false);
	*i += ft_strlen(to_find);
	return (true);
}

bool	final_decision(char *entry, char *suffix)
{
	char	*to_find;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	if (suffix == NULL)
		return (true);
	while (true)
	{
		if (ft_strchr(suffix + j, '*') == 0)
			return (get_last_suffix(suffix, entry, j, i));
		while (suffix != NULL && suffix[j] != '\0' && suffix[j] != '*')
			j++;
		to_find = ft_strndup(suffix + start, j - start);
		if (to_find == NULL)
			return (false);
		if (check_occurence(entry, to_find, &i) == false)
			return (free(to_find), false);
		start = ++j;
		free(to_find);
	}
	return (true);
}
