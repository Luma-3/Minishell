/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:40:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 15:59:03 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stackft.h"

char	*get_path_wildcard(char *arg, int index)
{
	char	*path;
	int		i;
	int 	len;

	i = index;
	while (ft_iswhitespace(arg[i]) == false && i >= 0 && arg[i] != '/')
		i--;
	if (i == -1 && arg[i] != '/')
	{
		path = getcwd(NULL, 0);
		return (path);
	}
	while (ft_iswhitespace(arg[i]) == false && i > 0)
		i--;
	if (i == 0)
		len = 1;
	else
		len = index - i;
	path = ft_strndup(arg + i, len);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_prefix(char *prompt, int index)
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

char	*get_suffix(char *prompt, int index)
{
	char	*suffix;
	int		i;

	i = index + 1;
	while (prompt[i] != '\0' && ft_iswhitespace(prompt[i]) == false
		&& prompt[i] != '/')
		i++;
	if (i == index + 1)
		return (NULL);
	suffix = ft_strndup(prompt + index + 1, i - index);
	if (suffix == NULL)
		return (NULL);
	return (suffix);
}

bool	find_match_file(char *entry, char *prefix, char *suffix)
{
	int	len_entry;
	int	len_prefix;
	int	len_suffix;

	len_prefix = 0;
	len_suffix = 0;
	if (suffix != NULL)
		len_suffix = ft_strlen(suffix);
	if (prefix != NULL)
		len_prefix = ft_strlen(prefix);
	if (entry != NULL)
		len_entry = ft_strlen(entry);
	if ((len_prefix == 0 && entry[0] != '.') || (len_prefix != 0 && prefix[0] == '.'))
	{
		if (ft_strncmp(entry, prefix, len_prefix) == 0 && ft_strncmp(entry + len_entry - len_suffix, suffix, len_suffix) == 0)
		{
			return true;
		}
	}
	return (false);
}

char	*get_token(char *prefix, char *suffix)
{
	char	*tmp;
	int		len_prefix;
	int		len_suffix;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_prefix = 0;
	len_suffix = 0;
	if (prefix != NULL)
		len_prefix = ft_strlen(prefix);
	if (suffix != NULL)
		len_suffix = ft_strlen(suffix);
	tmp = ft_calloc(len_prefix + len_suffix + 2, sizeof(char));
	if (!tmp)
		return (NULL);
	while (j < len_prefix)
		tmp[i++] = prefix[j++];
	tmp[i++] = '*';
	j = 0;
	while (j < len_suffix)
		tmp[i++] = suffix[j++];
	return (tmp);
}
