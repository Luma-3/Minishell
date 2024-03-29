/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:33:10 by anthony           #+#    #+#             */
/*   Updated: 2024/03/28 16:13:23 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <dirent.h>





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


