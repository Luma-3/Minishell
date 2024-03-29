/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:08:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 16:28:01 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static bool	find_match_file(char *entry, char *prefix, char *suffix)
{
	int	len_entry;
	int	len_prefix;
	int	len_suffix;

	len_prefix = 0;
	len_suffix = 0;
	if (prefix == NULL && suffix == NULL)
		return (false);
	if (suffix != NULL)
		len_suffix = ft_strlen(suffix);
	if (prefix != NULL)
		len_prefix = ft_strlen(prefix);
	if (entry != NULL)
		len_entry = ft_strlen(entry);
	if (ft_strncmp(entry, prefix, len_prefix) == 0
		&& ft_strncmp(entry + len_entry - len_suffix, suffix, len_suffix) == 0)
		return (true);
	return (false);
}

static char	*get_path_wildcard(char *arg, int index)
{
	char	*path;
	int		i;

	i = index;
	while (ft_iswhitespace(arg[i]) == false && i >= 0 && arg[i] != '/')
		i--;
	if (i == 0 && arg[i] != '/')
	{
		path = getcwd(NULL, 0);
		return (path);
	}
	while (ft_iswhitespace(arg[i - 1]) == false && i >= 0)
		i--;
	path = ft_strndup(arg + i, index - i);
	if (path == NULL)
		return (NULL);
	return (path);
}

static char	*get_prefix(char *prompt, int index)
{
	int	i;
	char	*prefix;

	i = index;
	while (index >= 0 && ft_iswhitespace(prompt[index - 1]) == false
		&& prompt[index - 1] != '/')
		index--;
	if (index == i)
		return (NULL);
	prefix = ft_strndup(prompt + index, i - index);
	if (prefix == NULL)
		return (NULL);
	return (prefix);
}

static char	*get_suffix(char *prompt, int index)
{
	char	*suffix;
	int		i;

	i = index = 1;
	while (prompt[i] != '\0' && ft_iswhitespace(prompt[i]) == false
		&& prompt[i] != '/')
		i++;
	if (i == index)
		return (NULL);
	suffix = ft_strndup(prompt + index + 1, i - index);
	if (suffix == NULL)
		return (NULL);
	return (suffix);
}

char	*find_data_all(t_maindata *core_data, const char *arg, int index)
{
	t_tree_asterisk	*tree;
	DIR				*dir;
	struct dirent	*entry;
	char			*prefix;
	char 			*suffix;
	char			*path;
	
	
	prefix = get_prefix(arg, index);
	suffix = get_suffix(arg, index);
	path = get_path_wildcard(arg, index);
	dir = opendir(path);
	if (dir == NULL)
	{
		errno = 0;
		return ((char *)arg);
	}

	
	return (new_arg);
}