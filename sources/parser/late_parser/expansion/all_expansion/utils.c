/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:49:00 by anthony           #+#    #+#             */
/*   Updated: 2024/04/11 11:56:03 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stackft.h"
#include "minishell.h"

char	*file_to_directory(t_match_file *match_file, char *file_name)
{
	struct stat		stat_file;
	char			*path;
	char			*buffer_name;

	buffer_name = ft_calloc(257, sizeof(char));
	if (buffer_name == NULL)
		return (NULL);
	path = ft_strjoin4(match_file->path, "/", file_name, "\0");
	if (path == NULL)
	{
		free(buffer_name);
		return (NULL);
	}
	stat(path, &stat_file);
	ft_strlcpy(buffer_name, file_name, 256);
	if (S_ISDIR(stat_file.st_mode))
	{
		ft_strlcat(buffer_name, "/", 257);
	}
	free(path);
	return (buffer_name);
}

t_match_file	*init_match_file(t_match_file *match_file, char *data, int i)
{
	match_file->suffix = get_suffix(data, i);
	match_file->path = get_path_wildcard(data, i);
	match_file->prefix = get_prefix(data, i);
	match_file->old_data = NULL;
	return (match_file);
}

void	no_access_file(t_dstack *stack, t_list **list, t_match_file *match_file)
{
	t_list	*new_node;
	char	*tmp;

	tmp = d_pop_stk(stack);
	new_node = ft_lstnew(tmp);
	if (new_node != NULL)
		ft_lstadd_front(list, new_node);
	else
		free(tmp);
	free_match_file(match_file);
	return ;
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

bool	verif_suffix_ptr(char *entry, char *suffix, int i)
{
	if (ft_findstr(entry, suffix, i) != -1)
		return (true);
	return (false);
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
				&& to_find[j] != '\0')
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
