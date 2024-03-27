/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:45:55 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 22:12:34 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"
#include <fcntl.h>

// static int	take_path(char *path)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("/etc/environment", O_RDONLY);
// 	if (fd == -1)
// 		return (perror("Safe Mode"), FAILURE);
// 	line = get_next_line(fd);
// 	close(fd);
// 	if (line == NULL)
// 		return (errno = ENOMEM, FAILURE);
// 	path = ft_strndup(line + 6, ft_strlen(line) - 8);
// 	if (path == NULL)
// 		return (errno = ENOMEM, FAILURE);
// 	return (SUCCESS);
// }

// static int	safe_env(t_list *env)
// {
// 	char	*cwd;

// 	cwd = getcwd(NULL, 0);
// 	if (cwd == NULL)
// 		return (errno = ENOMEM, FAILURE);
// 	if (ms_setenv(&env, "PWD", cwd) == FAILURE)
// 	{
// 		printf("PWD\n");
// 		return (free(cwd), FAILURE);
// 	}
// 	if (ms_setenv(&env, "_", "]") == FAILURE)
// 		return (free(cwd), FAILURE);
// 	return (SUCCESS);
// }

// int	safe_mode(t_maindata *core_data)
// {
// 	if (take_path(core_data->path) == FAILURE)
// 	{
// 		perror_switch(core_data->errors, "Safe Mode");
// 		return (FAILURE);
// 	}
// 	if (safe_env(core_data->env) == FAILURE)
// 	{
// 		perror_switch(core_data->errors, "Safe Mode2");
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }
