/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:49:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 18:31:21 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <utmp.h>
#include <fcntl.h>
#include "display.h"

static char	*take_u_name(void)
{
	int			fd;
	struct utmp	user;
	char		*uname;

	fd = open("/run/utmp", O_RDONLY);
	if (fd == -1)
		return (perror("Safe Mode"), NULL);
	while (read(fd, &user, sizeof(struct utmp)) > 0)
	{
		if (user.ut_type == USER_PROCESS)
		{
			uname = ft_strdup(user.ut_name);
			if (uname == NULL)
			{
				close(fd);
				errno = ENOMEM;
				return (perror("Safe Mode"), NULL);
			}
			return (uname);
		}
	}
	close(fd);
	return (NULL);
}

static int	launch_shell(t_maindata *core_data, char **envp)
{
	t_list	*env;

	env = NULL;
	printf("\033]0;KikiShell\007");
	get_history(core_data->history_fd);
	if (core_data->history_fd == FAILURE)
		return (perror_switch(core_data->errors, "KikiShell"), FAILURE);
	env = env_to_lst(envp);
	if (!env)
	{
		if (init_safe_mode(core_data) == FAILURE)
			return (FAILURE);
		display_msg(core_data, core_data->env, SAFE_MSG);
		return (SUCCESS);
	}
	core_data->env = env;
	display_msg(core_data, core_data->env, HELLO_MSG);
	return (SUCCESS);
}

int	init_shell(t_maindata *core_data, t_error *errors, char **envp)
{	
	ft_bzero(core_data, sizeof(t_maindata));
	__init_error__(errors);
	core_data->errors = errors;
	init_signal();
	core_data->uname = take_u_name();
	if (core_data->uname == NULL)
		return (perror_switch(errors, "KikiShell"), FAILURE);
	core_data->history_fd = open_history(".kiki_history",
			core_data->uname);
	return (launch_shell(core_data, envp));
}
