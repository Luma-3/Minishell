/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:34 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/26 14:59:16 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*path_to_tilde(t_list *env)
{
	char	*path_home;
	char	*path_absolute;
	char	*path_tmp;
	int		i;

	i = 0;
	path_tmp = ft_strdup(" ~ ");
	if (path_tmp == NULL)
		return (NULL);
	path_absolute = NULL;
	path_home = ms_getenv(env, "HOME");
	if (path_home == NULL)
		return (path_tmp);
	path_absolute = getcwd(path_absolute, 0);
	if (path_absolute == NULL)
		return (free(path_home), path_tmp);
	while (path_home[i] == path_absolute[i]
		&& path_home[i] && path_absolute[i])
		i++;
	free(path_home);
	path_home = ft_strjoin(" ~ ", path_absolute + i);
	if (path_home == NULL)
		return (free(path_home), free(path_absolute), path_tmp);
	(free(path_absolute), free(path_tmp));
	return (path_home);
}

char	*ft_get_chdir(void)
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

char *assemble(char **display)
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
