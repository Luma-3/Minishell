/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:02:03 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 17:44:47 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdin(t_error *errors, int fd)
{
	if (dup2(fd, STDIN_FILENO) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "dup2", NULL);
	}
	if (close(fd) == FAILURE)
	{
		errno = EIO;
		perror_switch(errors, "close", NULL);
	}
}

char	*get_home(const char *uname)
{
	char	*home;

	home = ft_strjoin("/home/", uname);
	if (home == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (home);
}
