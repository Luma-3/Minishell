/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:09:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 15:50:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

static void	print_env(void *env_val)
{
	ft_putendl_fd((char *)env_val, STDOUT_FILENO);
}

int	ms_env(const char *prompt, char **args, t_list **envp)
{
	(void)prompt;
	(void)args;
	ft_lstiter(*envp, print_env);
	return (EXIT_SUCCESS);
}