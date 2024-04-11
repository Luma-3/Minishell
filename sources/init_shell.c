/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:49:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 18:45:03 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <utmp.h>
#include <fcntl.h>
#include "display.h"
#include "ms_sig.h"

char	*get_uname(void)
{
	int			fd;
	struct utmp	user;
	char		*uname;

	fd = open("/var/run/utmp", O_RDONLY);
	if (fd == -1)
	{
		errno = ENOENT;
		return (NULL);
	}
	while (read(fd, &user, sizeof(struct utmp)) > 0)
	{
		if (user.ut_type == USER_PROCESS)
		{
			uname = ft_strdup(user.ut_name);
			if (uname == NULL)
			{
				close(fd);
				return (errno = ENOMEM, NULL);
			}
			return (close(fd), uname);
		}
	}
	close(fd);
	return (errno = ENOENT, NULL);
}

static bool	has_path(t_list *env)
{
	char	*path;

	path = ms_getenv(env, "PATH");
	if (path == NULL)
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

static int	launch_shell(t_maindata *core_data, char **envp)
{
	t_list	*env;

	env = NULL;
	printf("\033]0;KikiShell\007");
	get_history(core_data->history_fd);
	if (core_data->history_fd == FAILURE)
		return (perror_switch(core_data->errors, "KikiShell", NULL), FAILURE);
	env = env_to_lst(envp);
	if (!env || has_path(env) == false)
	{
		core_data->env = env;
		if (init_safe_mode(core_data) == FAILURE)
			return (FAILURE);
		display_msg(core_data, SAFE_MSG);
		return (SUCCESS);
	}
	core_data->env = env;
	display_msg(core_data, HELLO_MSG);
	return (SUCCESS);
}

int	init_shell(t_maindata *core_data, t_error *errors, char **envp)
{
	ft_bzero(core_data, sizeof(t_maindata));
	__init_error__(errors);
	core_data->errors = errors;
	init_signal();
	core_data->uname = get_uname();
	if (core_data->uname == NULL)
		return (perror_switch(errors, "KikiShell", NULL), FAILURE);
	core_data->history_fd = open_history(HISTORY_FILE,
			core_data->uname);
	return (launch_shell(core_data, envp));
}
