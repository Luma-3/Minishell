/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:40:50 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 13:27:05 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"

int	ms_unset(char **args, t_list **envp, t_error *errors)
{
	(void)errors;
	args++;
	while (*args)
	{
		ms_unsetenv(envp, *args);
		args++;
	}
	return (EXIT_SUCCESS);
}
