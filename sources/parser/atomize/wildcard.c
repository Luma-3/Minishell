/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:33:10 by anthony           #+#    #+#             */
/*   Updated: 2024/03/27 01:34:06 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <dirent.h>

static char	*get_path_prefix(char *prompt, int index)
{
	int	i;

	i = index;
	while (ft_iswhitespace(prompt[index]) == false
		&& index >= 0 && prompt[index] != '/')
		index--;
	return (ft_strndup(prompt + index, i - index));
}

static char	*get_path_wildcard(char *prompt, int index)
{
	char	*path;
	int		i;

	i = index;
	while (ft_iswhitespace(prompt[i]) == false && i >= 0)
		i--;
	path = ft_strndup(prompt - index, index - i + 1);
	if (path == NULL)
		return (NULL);
	return (path);
}

static  char	*get_current_file(char *prompt, int index)
{
	DIR		*dir;
	char	*path;
	char	*current_file;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	while (readdir(dir)->d_name != NULL)
	{
		current_file = readdir(dir)->d_name;
		if (current_file[0] == '.')
			continue ;
		prompt = put_wildcard(prompt, current_file, ' ', index);
		index += ft_strlen(current_file);
		printf("PROMPT = %s\n", prompt);
	}
	return (path);
}

static char	*copy_all_files(char *prompt, int index)
{
	// DIR				*dir;
	// struct dirent	*entry;
	char			*prefix;
	// char			*suffix;
	char			*path;
	int				i;

	prefix = NULL;
	i = index;
	// dir = NULL;
	printf("index = %d\n", index);
	prefix = get_path_prefix(prompt, index);
	if (prompt[i - 1] == '/')
	{
		printf("GO TO GET PATH WILDCARD\n");
		path = get_path_wildcard(prompt, index);
	}
	else if (prompt[i - 1] == ' ')
	{
		printf("GO TO GET CURRENT FILE\n");
		path = get_current_file(prompt, index);
	}

	(void)path;
	(void)prefix;
	// dir = opendir(path);
	// if (path == NULL)
	// {
	// 	errno = 0;
	// 	return (prompt);
	// }
	// // suffix = get_suffix(core_data, prompt, index);
	// while (entry != NULL)
	// {
	// 	entry = readdir(dir);
	// 	if (ft_strncmp(entry->d_name, prefix, ft_strlen(prefix)) == 0) //TODO RVERSE STRNCMP
	// 		prompt = copy_data_wildcard(core_data, ft_strdup(entry->d_name), ' ', index);
	// }
	return (prompt);
}

char	*handle_wildcard(t_maindata *core_data, char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '$' && prompt[i + 1] != '\0')
			prompt = copy_data_wildcard(core_data,
					get_wildcard(prompt, i + 1), '$', i);
		else if (prompt[i] == '~' && is_tilde_to_replace(prompt, i) == true)
			prompt = copy_data_wildcard(core_data, ft_strdup("HOME"), '~', i);
		else if (prompt[i] == '*')
			prompt = copy_all_files(prompt, i);
		i++;
	}
	return (prompt);
}
