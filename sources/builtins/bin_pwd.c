/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:04:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 11:09:41 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

int	ms_pwd(char **args, t_list **envp, void *data)
{
	char	*cwd;

	(void)args;
	(void)envp;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		errno = ENOMEM;
		perror_switch((t_error *)data, "pwd");
		return (errno);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
