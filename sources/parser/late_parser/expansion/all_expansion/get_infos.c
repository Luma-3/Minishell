/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:40:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 01:33:56 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stackft.h"

char	*get_path_wildcard(char *arg, int index)
{
	char	*path;
	char	*path_tmp;
	int		i;

	path_tmp = getcwd(NULL, 0);
	if (path_tmp == NULL)
		return (NULL);
	i = index;
	while (i > 0 && arg[i] != '/')
		i--;
	if (arg[i] != '/' && i == 0)
	{
		path = ft_strjoin(path_tmp, "/");
		free(path_tmp);
		if (path == NULL)
			return (NULL);
		return (path);
	}
	free(path_tmp);
	path = ft_strndup(arg, i + 1);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_prefix(char *arg, int index)
{
	int		i;
	char	*prefix;

	if (index == 0 || arg[index - 1] == '/')
		return (NULL);
	i = index;
	while (i > 0 && arg[i] != '/')
		i--;
	if (arg[i] == '/')
		i++;
	prefix = ft_strndup(arg + i, index - i);
	if (prefix == NULL)
		return (NULL);
	return (prefix);
}

char	*get_suffix(char *arg, int index)
{
	char	*suffix;
	int		i;

	suffix = NULL;
	while (arg[index] && arg[index] == '*')
		index++;
	i = index;
	if (arg[i] == '\0' || arg[i] == '/')
		return (NULL);
	while (arg[i] != '\0' && arg[i] != '/')
		i++;
	suffix = ft_strndup(arg + index, i - index);
	if (suffix == NULL)
		return (NULL);
	return (suffix);
}

char	*get_token(char *prefix, char *suffix)
{
	char	*new_str;

	if (prefix == NULL && suffix == NULL)
	{
		new_str = ft_strdup("*");
	}
	else if (prefix == NULL)
	{
		new_str = ft_strjoin("*", suffix);
	}
	else if (suffix == NULL)
	{
		new_str = ft_strjoin(prefix, "*");
	}
	else
	{
		char sucide[1];
		sucide[0] = '\0';
		new_str = ft_strjoin4(prefix, "*", suffix, sucide);
		//TODO changer ft-strjoin 4 avec les ft_strle
	}
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

char	*get_replace_token(t_match_file *match_file, t_dstack *stack)
{
	char	*token;

	match_file->old_data = (char *)d_pop_stk(stack);
	token = get_token(match_file->prefix, match_file->suffix);
	if (token == NULL)
		return (NULL);
	return (token);
}
