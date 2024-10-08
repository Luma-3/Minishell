/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:09:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 11:08:16 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

static void	print_env(void *env_val)
{
	ft_putendl_fd((char *)env_val, STDOUT_FILENO);
}

int	ms_env(char **args, t_list **envp, void *data)
{
	(void)args;
	(void)data;
	ft_lstiter(*envp, print_env);
	return (EXIT_SUCCESS);
}
