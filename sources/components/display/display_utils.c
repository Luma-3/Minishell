/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:34 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/11 12:34:59 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*path_to_tilde(t_list *env)
{
	char	*cwd;
	char	*home;
	char	*path;
	int		i;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	home = ms_getenv(env, "HOME");
	if (home == NULL)
		return (cwd);
	i = 0;
	while (cwd[i] && home[i] && cwd[i] == home[i])
		i++;
	if (home[i] == '\0' && (cwd[i] == '/' || cwd[i] == '\0'))
	{
		path = ft_insert_str(cwd, "~", home, 0);
		free(home);
		if (path == cwd)
			return (cwd);
		free(cwd);
		return (path);
	}
	free(home);
	return (cwd);
}

char	*get_current_dir(void)
{
	char	*absolute_path;
	char	*working_directory;
	long	len;

	absolute_path = getcwd(NULL, 0);
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

char	*assemble(const char **display)
{
	char	*display_final;
	int		i;
	size_t	len;

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
