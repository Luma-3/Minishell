/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:04:59 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 14:13:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

int	ms_pwd(char **args, t_list **envp, t_error *errors)
{
	char	*cwd;

	(void)errors;
	(void)args;
	(void)envp;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		errno = ENOMEM;
		perror_switch(errors, "pwd");
		return (errno);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
