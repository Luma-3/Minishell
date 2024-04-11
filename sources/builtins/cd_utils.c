/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:18:33 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 14:29:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "minishell.h"

char	*spec_token(t_error *errors)
{
	char	*home;
	char	*uname;

	uname = get_uname();
	if (uname == NULL)
	{
		perror_switch(errors, "cd", NULL);
		return (NULL);
	}
	home = get_home(uname);
	free(uname);
	if (home == NULL)
	{
		perror_switch(errors, "cd", NULL);
		return (NULL);
	}
	return (home);
}

char	*oldpwd_token(t_list **env)
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

int	set_pwds(t_list **env, t_error *error)
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
	if (pwd == NULL && errno != ENOENT)
	{
		perror_switch(error, "cd", NULL);
		return (free(oldpwd), errno);
	}
	if (ms_setenv(env, "PWD", pwd) == FAILURE
		|| ms_setenv(env, "OLDPWD", oldpwd) == FAILURE)
	{
		free(pwd);
		free(oldpwd);
		return (errno);
	}
	free(pwd);
	free(oldpwd);
	return (SUCCESS);
}
