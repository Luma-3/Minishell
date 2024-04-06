/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:18:28 by anthony           #+#    #+#             */
/*   Updated: 2024/04/06 14:31:51 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

bool	identify_file(struct dirent *entry, t_match_file *match_file)
{
	char	*file_name;
	bool	result;

	file_name = file_to_directory(match_file, entry->d_name);
	if (file_name == NULL)
		return (false);
	if (find_match_file(file_name, match_file->prefix,
		match_file->suffix) == false)
		result = false;
	else
		result = true;
	free(file_name);
	return (result);
}

static char	*get_replace_token(t_match_file *match_file, t_dstack *stack)
{
	char	*token;
	char	*suffix_tmp;

	match_file->old_data = (char *)d_pop_stk(stack);
	suffix_tmp = ft_strtrim(match_file->suffix, "/");
	if (suffix_tmp == NULL)
		return (NULL);
	token = get_token(match_file->prefix, suffix_tmp);
	free(suffix_tmp);
	if (token == NULL)
		return (NULL);
	return (token);
}

bool	find_and_push(t_dstack *stack, t_match_file *match_file,
	DIR *dir, int i)
{
	struct dirent	*entry;
	char			*token;
	bool			have_file;

	have_file = false;
	token = get_replace_token(match_file, stack);
	if (token == NULL)
		return (false);
	while (true)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (identify_file(entry, match_file) == true)
		{
			have_file = true;
			d_push_stk(stack, ft_insert_str(match_file->old_data,
					entry->d_name, token, i));
		}
	}
	return (free(token), have_file);
}

static bool	get_last_suffix(char *suffix, char *entry, int j, int i)
{
	int		len_suff;
	char	*suffix_dir;

	len_suff = ft_strlen(suffix + j);
	if (len_suff != 0)
	{
		if (ft_strchr(suffix + j, '/') == 0)
		{
			suffix_dir = ft_strjoin(suffix + j, "/");
			if (suffix_dir != NULL)
			{
				if (decision_file(entry, suffix + j) == true
					|| decision_directory(entry, suffix_dir) == true)
					return (verif_suffix_ptr(entry, suffix + j, suffix_dir, i));
			}
		}
		else if (decision_directory(entry, suffix + j) == true)
			return (verif_suffix_ptr(entry, suffix + j, NULL, i));
	}
	return (false);
}

static	bool	final_decision(char *entry, char *suffix)
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
		if (ft_findstr(entry, to_find, i) == -1)
			return (false);
		i = ft_findstr(entry, to_find, i) + ft_strlen(to_find);
		start = ++j;
	}
	return (true);
}

bool	find_match_file(char *entry, char *prefix, char *suffix)
{
	int		len_prefix;
	int		len_suffix;

	len_prefix = 0;
	len_suffix = 0;
	if (suffix != NULL)
		len_suffix = ft_strlen(suffix);
	if (prefix != NULL)
		len_prefix = ft_strlen(prefix);
	if (len_prefix == 0 && len_suffix == 0)
	{
		if (entry[0] != '.')
			return (true);
		return (false);
	}
	if (len_prefix == 0 && entry[0] == '.')
		return (false);
	if (len_prefix == 0 && only_all(suffix) == true)
		return (true);
	if ((ft_strncmp(entry, prefix, len_prefix) == 0
			&& len_suffix == 0)
		|| (ft_strncmp(entry, prefix, len_prefix) == 0
			&& final_decision(entry, suffix) == true))
		return (true);
	return (false);
}
