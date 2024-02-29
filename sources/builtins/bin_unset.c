/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:40:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 16:01:58 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int	ms_unset(const char *prompt, char **args, t_list **envp)
{
	(void)prompt;
	args++;
	while (*args)
	{
		ms_unsetenv(envp, *args);
		args++;
	}
	return (EXIT_SUCCESS);
}
