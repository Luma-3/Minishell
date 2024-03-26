/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:49:00 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 15:49:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <utmp.h>
#include <fcntl.h>

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
			printf("uname = %s\n", uname);
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

int	init_shell(t_maindata *core_data, t_error *errors, t_list *env, char **envp)
{
	printf("\033]0;KikiShell\007");
	__init_error__(errors);
	init_signal();
	ft_bzero(core_data, sizeof(t_maindata));
	core_data->errors = errors;
	core_data->uname = take_u_name();
	if (core_data->uname == NULL)
		return (perror_switch(errors, "KikiShell1"), FAILURE);
	printf("ccuname = %s\n", core_data->uname);
	core_data->history_fd = open_history(".kiki_history",
			core_data->uname);
	get_history(core_data->history_fd);
	if (core_data->history_fd == FAILURE)
		return (perror_switch(errors, "KikiShell2"), FAILURE);
	env = env_to_lst(envp);
	if (!env)
	{
		printf("GO to safe mode\n");
		if (safe_mode(core_data) == FAILURE)
			return (FAILURE);
	}
	core_data->env = env;
	return (SUCCESS);
}
