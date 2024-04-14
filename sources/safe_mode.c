/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:45:55 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:40:36 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"
#include <fcntl.h>

static void	close_gnl(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
	}
}

static char	*take_path(void)
{
	int		fd;
	char	*line;
	char	*path;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		return (perror("Safe Mode"), NULL);
	line = get_next_line(fd);
	close_gnl(fd);
	close(fd);
	if (line == NULL)
		return (errno = ENOMEM, NULL);
	path = ft_strndup(line + 6, ft_strlen(line) - 8);
	free(line);
	if (path == NULL)
		return (errno = ENOMEM, NULL);
	return (path);
}

static int	safe_env(t_list **env)
{
	char	*cwd;

	if (ms_setenv(env, "_", "]") == FAILURE)
		return (FAILURE);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (errno = ENOMEM, FAILURE);
	if (ms_setenv(env, "PWD", cwd) == FAILURE)
	{
		free(cwd);
		return (FAILURE);
	}
	free(cwd);
	return (SUCCESS);
}

int	init_safe_mode(t_core *core_data)
{
	core_data->path = take_path();
	if (core_data->path == NULL)
	{
		perror_switch(core_data->errors, "Safe Mode", NULL);
		return (FAILURE);
	}
	if (safe_env(&(core_data->env)) == FAILURE)
	{
		perror_switch(core_data->errors, "Safe Mode", NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}
