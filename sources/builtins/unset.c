/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:40:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 11:50:41 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int	ms_unset(const char *prompt, const char **args, t_list *envp)
{
	while (*args)
	{
		ms_unsetenv(envp, *args);
		args++;
	}
	return (EXIT_SUCCESS);
}