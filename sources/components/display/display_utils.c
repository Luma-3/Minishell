/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:34 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/03 16:34:15 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*path_to_tilde(t_list *env)
{
	char	*path_home;
	char	*path_absolute;
	int		i;

	i = 0;
	path_absolute = getcwd(NULL, 0);
	if (path_absolute == NULL)
		return (ft_strdup("I am lost"));
	path_home = ms_getenv(env, "HOME");
	if (path_home == NULL)
		return (ft_strjoin(" ", path_absolute));
	while (path_home[i] == path_absolute[i]
		&& path_home[i] && path_absolute[i])
		i++;
	free(path_home);
	path_home = ft_strjoin(" ~", path_absolute + i);
	if (path_home == NULL)
		return (path_absolute);
	free(path_absolute);
	return (path_home);
}

char	*get_current_dir(void)
{
	char	*absolute_path;
	char	*working_directory;
	int		len;

	absolute_path = NULL;
	absolute_path = getcwd(absolute_path, 0);
	if (absolute_path == NULL)
		return (NULL);
	len = ft_strlen(absolute_path);
	while (len >= 0 && absolute_path[len - 1] != '/')
		len--;
	working_directory = ft_strndup(absolute_path + len,
			ft_strlen(absolute_path) - len);
	if (working_directory == NULL)
	{
		errno = ENOMEM;
		free(absolute_path);
		return (NULL);
	}
	free(absolute_path);
	return (working_directory);
}

char	*assemble(char **display)
{
	char	*display_final;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (display[i] != NULL)
		len += ft_strlen(display[i++]);
	display_final = ft_calloc(sizeof(char), len + 1);
	if (display_final == NULL)
		return (NULL);
	i = 0;
	while (display[i] != NULL)
		ft_strlcat(display_final, display[i++], len + 1);
	return (display_final);
}
