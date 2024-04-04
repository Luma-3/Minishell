/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:43:35 by anthony           #+#    #+#             */
/*   Updated: 2024/04/04 12:55:58 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	b

static bool	get_last_suffix(char *suffix, char *entry, int j, int i)
{
	int		len_suff;
	int		len_suff_dir;
	char	*suffix_dir;

	suffix_dir = NULL;
	len_suff_dir = 0;
	len_suff = ft_strlen(suffix + j);
	if (len_suff == 0)
		return (true);
	if (ft_strchr(suffix + j, '/') == 0)
	{
		suffix_dir = ft_strjoin(suffix + j, "/");
		len_suff_dir = ft_strlen(suffix_dir);
		if ((ft_strncmp(entry + ft_strlen(entry) - ft_strlen(suffix + j), suffix + j, ft_strlen(suffix + j)) == 0)
			|| (ft_strncmp(entry + ft_strlen(entry) - len_suff_dir, suffix_dir, len_suff_dir) == 0))
		{
			if (ft_findstr(entry, suffix + j, i) != -1
				|| ft_findstr(entry, suffix_dir + j, i) != -1)
				return (true);
		}
		return (false);
	}
	if (ft_strncmp(entry + (int)ft_strlen(entry) - len_suff, suffix + j, len_suff) == 0)
	{
		if (ft_findstr(entry, suffix + j, i) != -1)
			return (true);
	}
	return (false);
}