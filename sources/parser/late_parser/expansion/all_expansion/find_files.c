/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:18:28 by anthony           #+#    #+#             */
/*   Updated: 2024/04/12 12:45:34 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

static char	*dup_push(char *old_data, char *entry, char *token, int i)
{
	char	*filename;
	char	*tmp;

	filename = ft_insert_str(old_data, entry, token, i);
	if (filename == old_data)
	{
		tmp = ft_strdup(old_data);
		if (tmp == NULL)
			return (NULL);
		return (tmp);
	}
	return (filename);
}

bool	get_last_suffix(char *suffix, char *entry, int j, int i)
{
	size_t		len_suff;
	char		*suffix_dir;

	len_suff = ft_strlen(suffix + j);
	if (len_suff == 0)
		return (true);
	if (ft_strchr(suffix + j, '/') == NULL)
	{
		suffix_dir = ft_strjoin(suffix + j, "/");
		if (suffix_dir == NULL)
			return (false);
		if (decision_file(entry, suffix + j) == true
			|| decision_directory(entry, suffix_dir) == true)
		{
			if (verif_suffix_ptr(entry, suffix + j, i) == true
				|| verif_suffix_ptr(entry, suffix_dir, i) == true)
				return (free(suffix_dir), true);
			return (free(suffix_dir), false);
		}
		free(suffix_dir);
	}
	else if (decision_directory(entry, suffix + j) == true)
		return (verif_suffix_ptr(entry, suffix + j, i));
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
	if (len_prefix == 0)
	{
		if (entry[0] == '.')
			return (false);
	}
	if (len_prefix == 0 && only_all(suffix) == true)
		return (true);
	if ((ft_strncmp(entry, prefix, len_prefix) == 0 && len_suffix == 0)
		|| (ft_strncmp(entry, prefix, len_prefix) == 0
			&& final_decision(entry, suffix) == true))
		return (true);
	return (false);
}

static bool	validate_file(struct dirent *entry, t_match_file *match_file)
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

bool	find_files(t_dstack *stack, t_match_file *match_file, DIR *dir, int i)
{
	struct dirent	*entry;
	char			*token;
	char			*tmp;
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
		if (validate_file(entry, match_file) == true)
		{
			have_file = true;
			tmp = dup_push(match_file->old_data, entry->d_name, token, i);
			if (tmp == NULL)
				return (free(token), false);
			d_push_stk(stack, tmp);
		}
	}
	return (free(token), have_file);
}
