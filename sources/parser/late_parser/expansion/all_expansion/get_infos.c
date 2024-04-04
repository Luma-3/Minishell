/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:40:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/04 10:26:51 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stackft.h"

char	*get_path_wildcard(char *arg, int index)
{
	char	*path;
	int		i;
	int		len;

	path = NULL;
	i = index;
	while (i >= 0 && arg[i] != '/')
	{
		if (i == 0)
			return (getcwd(NULL, 0));
		i--;
	}
	len = i;
	if (len == 0)
		return (ft_strdup("/"));
	path = ft_strndup(arg, len + 1);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*get_prefix(char *arg, int index)
{
	int		i;
	char	*prefix;

	prefix = NULL;
	i = index;
	while (i >= 0 && arg[i] != '/')
	{
		if (i == 0)
			break ;
		i--;
	}
	if (i == index - 1 && arg[i] == '/')
		return (NULL);
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
	i = index + 1;
	while (arg[i] != '\0' && arg[i] != '/')
		i++;
	suffix = ft_strndup(arg + index + 1, i - index);
	if (suffix == NULL)
		return (NULL);
	return (suffix);
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
