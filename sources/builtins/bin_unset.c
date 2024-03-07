/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:40:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 11:09:10 by antgabri         ###   ########.fr       */
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
