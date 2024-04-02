/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 13:23:15 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "minishell.h"

static char	*spec_token(t_error *errors)
{
	char	*home;
	char	*uname;

	uname = get_uname();
	if (uname == NULL)
	{
		perror_switch(errors, "cd");
		return (NULL);
	}
	home = get_home(uname);
	free(uname);
	if (home == NULL)
	{
		perror_switch(errors, "cd");
		return (NULL);
	}
	return (home);
}

static char	*oldpwd_token(t_list **env)
{
	char	*oldpwd;

	oldpwd = ms_getenv(*env, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (oldpwd);
}

int	ms_cd(char **args, t_list **env, t_error *errors)
{
	char	*chdir_path;

	chdir_path = args[1];
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		chdir_path = spec_token(errors);
		if (chdir_path == NULL)
			return (ENOMEM);
	}
	else if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		chdir_path = oldpwd_token(env);
		if (chdir_path == NULL)
			return (EPERM);
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(args[1], STDERR_FILENO);
		return (errno);
	}
	return (EXIT_SUCCESS);
}
