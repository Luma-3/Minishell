/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:00:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 12:11:19 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

int ms_cd(const char *prompt, const char **args, t_list *envp)
{
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(args[1], STDERR_FILENO);
		return (errno);
	}
	return (EXIT_SUCCESS);	
}
