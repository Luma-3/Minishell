/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:27:09 by anthony           #+#    #+#             */
/*   Updated: 2024/04/06 12:28:16 by anthony          ###   ########.fr       */
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

bool	verif_suffix_ptr(char *entry, char *suffix, char *suffix_dir, int i)
{
	if (ft_findstr(entry, suffix, i) != -1)
		return (true);
	if (suffix_dir != NULL && ft_findstr(entry, suffix_dir, i) != -1)
		return (true);
	return (false);
}
