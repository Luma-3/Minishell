/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:33:10 by anthony           #+#    #+#             */
/*   Updated: 2024/03/27 16:35:04 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <dirent.h>

// static char	*get_prefix(char *prompt, int index)
// {
// 	int	i;

// 	i = index;
// 	while (index >= 0 && ft_iswhitespace(prompt[index - 1]) == false
// 		&& prompt[index - 1] != '/')
// 		index--;
// 	if (index == i)
// 		return (NULL);
// 	return (ft_strndup(prompt + index, i - index));
// }

// static char	*get_suffix(char *prompt, int index)
// {
// 	int	i;

// 	i = index;
// 	while (prompt[i + 1] != '\0' && ft_iswhitespace(prompt[i + 1]) == false
// 		&& prompt[i + 1] != '/')
// 		i++;
// 	if (i == index)
// 		return (NULL);
// 	return (ft_strndup(prompt + index + 1, i - index));
// }

// static char	*get_path_wildcard(char *prompt, int index)
// {
// 	char	*path;
// 	int		i;

// 	i = index;
// 	while (ft_iswhitespace(prompt[i]) == false && i >= 0)
// 		i--;
// 	path = ft_strndup(prompt + (i + 1), index - i);
// 	return (path);
// }

// static bool	find_match_file(char *entry, char *prefix, char *suffix)
// {
// 	int	len_entry;
// 	int	len_prefix;
// 	int	len_suffix;

// 	len_entry = 0;
// 	len_prefix = 0;
// 	len_suffix = 0;
// 	if (prefix == NULL && suffix == NULL)
// 		return (false);
// 	if (suffix != NULL)
// 		len_suffix = ft_strlen(suffix);
// 	if (prefix != NULL)
// 		len_prefix = ft_strlen(prefix);
// 	if (entry != NULL)
// 		len_entry = ft_strlen(entry);
// 	if (prefix != NULL && ft_strncmp(entry, prefix, len_prefix) == 0)
// 		return (true);
// 	while (suffix != NULL && entry[len_entry - 1] == suffix[len_suffix - 1])
// 	{
// 		len_entry--;
// 		len_suffix--;
// 		if (len_suffix == 0)
// 			return (true);
// 	}
// 	return (false);
// }

// static char	*copy_all_files(char *prompt, int index)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	char			*prefix;
// 	char			*suffix;
// 	char			*path;
// 	int				i;

// 	prefix = NULL;
// 	i = index;
// 	prefix = get_prefix(prompt, index);
// 	index = place_cursor_before_prefix(prompt, index);
// 	printf("index = %d\n", index);
// 	if (prompt[index] == '/')
// 	{
// 		path = get_path_wildcard(prompt, index);
// 	}
// 	else
// 	{
// 		path = getcwd(NULL, 0);
// 	}
// 	suffix = get_suffix(prompt, i);
// 	dir = opendir(path);
// 	if (path == NULL)
// 	{
// 		errno = 0;
// 		return (prompt);
// 	}
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		while (find_match_file(entry->d_name, prefix, suffix) == false)
// 			continue ;
// 		if (entry != NULL)
// 		{
// 			printf("FOUND OCCURENCE\n");
// 			prompt = put_wildcard(prompt, entry->d_name, '*', index);
// 			index += ft_strlen(entry->d_name) + 1;
// 			prompt = put_wildcard(prompt, " ", ' ', index);
// 			index++;
// 		}
// 	}
// 	printf("COPY ALL FILES\n");
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (entry->d_name[0] == '.')
// 			continue ;
// 		prompt = put_wildcard(prompt, entry->d_name, ' ', index);
// 		index += ft_strlen(entry->d_name);
// 		prompt = put_wildcard(prompt, " ", ' ', index);
// 		index++;
// 	}
// 	return (prompt);
// }

int	handle_wildcard(t_maindata *core_data, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '~'))
			handle_tilde();
		if (ft_strchr ($))
			handle_dollar();
		if (ft_strchr(argv[i], '*'))
			hanlde_all
	}
	return (SUCCESS);
}
