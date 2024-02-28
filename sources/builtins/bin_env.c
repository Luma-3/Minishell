/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:09:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 15:56:20 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

static void	print_env(t_list *envp)
{
	while (envp)
	{
		ft_putendl_fd(envp->content, STDOUT_FILENO);
		envp = envp->next;
	}
}

int	ms_env(const char *prompt, char **args, t_list *envp)
{
	(void)prompt;
	(void)args;
	print_env(envp);
	return (EXIT_SUCCESS);
}