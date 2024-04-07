/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 16:57:19 by jbrousse         ###   ########.fr       */
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

static int	set_pwds(t_list **env, t_error *error)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = ms_getenv(*env, "PWD");
	if (oldpwd == NULL)
	{
		ft_putstr_fd("cd: PWD not set\n", STDERR_FILENO);
		return (FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		free(oldpwd);
		perror_switch(error, "cd");
		return (errno);
	}
	if (ms_setenv(env, "PWD", pwd) == FAILURE
		|| ms_setenv(env, "OLDPWD", oldpwd) == FAILURE)
	{
		free(pwd);
		free(oldpwd);
		return (errno);
	}
	return (SUCCESS);
}

static char	*get_chdir_path(char **args, t_list **env, t_error *errors)
{
	char	*chdir_path;

	if (!args[1])
	{
		chdir_path = spec_token(errors);
		if (chdir_path == NULL)
			return (NULL);
	}
	else if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		chdir_path = oldpwd_token(env);
		if (chdir_path == NULL)
			return (NULL);
	}
	else
	{
		chdir_path = ft_strdup(args[1]);
		if (chdir_path == NULL)
			return (NULL);
	}
	return (chdir_path);
}

int	ms_cd(char **args, t_list **env, t_error *errors)
{
	char	*chdir_path;

	chdir_path = get_chdir_path(args, env, errors);
	if (chdir_path == NULL)
		return (errno);
	else if (chdir(chdir_path) == -1)
	{
		free(chdir_path);
		perror("cd");
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(args[1], STDERR_FILENO);
		return (errno);
	}
	free(chdir_path);
	return (set_pwds(env, errors));
}
