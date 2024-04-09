/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 11:37:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "minishell.h"

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

int	ms_cd(char **args, t_list **env, void *data)
{
	char	*chdir_path;

	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	chdir_path = get_chdir_path(args, env, (t_error *)data);
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
	return (set_pwds(env, (t_error *)data));
}
