/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 17:01:00 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include <env.h>

int ms_cd(const char *prompt, char **args, t_list **envp)
{
	(void)prompt;
	(void)envp;
	if (!args[1] || !ft_strncmp(args[1], "~", 1))
	{
		if (chdir(ms_getenv(*envp, "HOME")) == -1)
		{
			perror("cd");
			return (errno);
		}
		return (EXIT_SUCCESS);
	}
	else if (chdir(args[1]) == -1)
	{
		perror("cd");
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(args[1], STDERR_FILENO);
		return (errno);
	}
	return (EXIT_SUCCESS);	
}
