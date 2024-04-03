/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:18:28 by anthony           #+#    #+#             */
/*   Updated: 2024/04/03 10:42:49 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

static char	*file_to_directory(t_match_file *match_file, char *file_name)
{
	struct stat		stat_file;
	char			*path;
	char			*buffer_name;

	buffer_name = ft_calloc(257, sizeof(char));
	if (buffer_name == NULL)
		return (NULL);
	path = ft_strjoin4(match_file->path, "/", file_name, "\0");
	stat(path, &stat_file);
	ft_strlcpy(buffer_name, file_name, 256);
	if (S_ISDIR(stat_file.st_mode))
	{
		ft_strlcat(buffer_name, "/", 257);
	}
	free(path);
	return (buffer_name);
}

bool	find_and_push(t_dstack *stack, t_match_file *match_file,
	DIR *dir, int i)
{
	struct dirent	*entry;
	char			*file_name;
	char			*token;
	bool			have_file;

	have_file = false;
	match_file->old_data = (char *)d_pop_stk(stack);
	token = get_token(match_file->prefix, ft_strtrim(match_file->suffix, "/"));
	if (token == NULL)
		return (have_file);
	while (true)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		file_name = file_to_directory(match_file, entry->d_name);
		if (find_match_file(file_name, match_file->prefix,
				match_file->suffix) == true)
		{
			have_file = true;
			d_push_stk(stack, ft_insert_str(match_file->old_data,
					entry->d_name, token, i));
		}
	}
	return (free(token), have_file);
}

static bool	final_judge(char *entry, char *suffix, int len_entry)
{
	int		len_suff;
	int		len_suff_dir;
	char	*suffix_dir;

	suffix_dir = NULL;
	len_suff_dir = 0;
	len_suff = ft_strlen(suffix);
	if (suffix != NULL && ft_strchr(suffix, '/') == 0)
	{
		suffix_dir = ft_strjoin(suffix, "/");
		len_suff_dir = ft_strlen(suffix_dir);
		if ((ft_strncmp(entry + len_entry - len_suff, suffix, len_suff) == 0)
			|| (ft_strncmp(entry + len_entry - len_suff_dir,
					suffix_dir, len_suff_dir) == 0))
			return (true);
	}
	else
	{
		if (ft_strncmp(entry + len_entry - len_suff, suffix, len_suff) == 0)
			return (true);
	}
	return (false);
}

bool	find_match_file(char *entry, char *prefix, char *suffix)
{
	int		len_prefix;
	int		len_suffix;
	int		len_entry;

	len_prefix = 0;
	len_suffix = 0;
	len_entry = ft_strlen(entry);
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
	if (ft_strncmp(entry, prefix, len_prefix) == 0
		&& final_judge(entry, suffix, len_entry) == true)
	{
		return (true);
	}
	return (false);
}
