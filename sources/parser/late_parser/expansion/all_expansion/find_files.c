/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:18:28 by anthony           #+#    #+#             */
/*   Updated: 2024/04/04 16:58:56 by jbrousse         ###   ########.fr       */
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
		if (file_name == NULL)
			return (free(token), false);
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

int	ft_findstr(char *str, char *to_find, int i)
{
	int		j;

	j = 0;
	while (str[i] != '\0')
	{
		if (to_find != NULL && str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j]
				&& to_find[j] != '\0' && str[i + j] != '\0')
			{
				j++;
			}
			if (to_find[j] == '\0')
				return (i);
			j = 0;
		}
		i++;
	}
	return (-1);
}

static bool	get_last_suffix(char *suffix, char *entry, int j, int i)
{
	int		len_suff;
	int		len_suff_dir;
	char	*suffix_dir;

	suffix_dir = NULL;
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

static	bool	final_decision(char *entry, char *suffix)
{
	char	*to_find;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	while (true)
	{
		if (ft_strchr(suffix + j, '*') == 0)
			return (get_last_suffix(suffix, entry, j, i));
		while (suffix != NULL && suffix[j] != '\0' && suffix[j] != '*')
			j++;
		to_find = ft_strndup(suffix + start, j - start);
		if (ft_findstr(entry, to_find, i) == -1)
			return (false);
		i = ft_findstr(entry, to_find, i) + ft_strlen(to_find);
		j++;
		start = j;
	}
	return (true);
}

bool	only_all(char *suffix)
{
	int	i;

	i = 0;
	while (suffix != NULL && suffix[i] == '*')
		i++;
	if (suffix != NULL && suffix[i] == 0)
		return (true);
	return (false);
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
