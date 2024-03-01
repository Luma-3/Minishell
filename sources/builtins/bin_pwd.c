/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:04:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 15:35:36 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

int	ms_pwd(const char *prompt, char **args, t_list **envp)
{
	char	*cwd;

	(void)prompt;
	(void)args;
	(void)envp;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (errno);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
