/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 11:50:35 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int	ms_export(const char *prompt, const char **args, t_list *envp)
{
	int		i;
	char 	*delimiter;

	i = 0;
	while (args[i])
	{
		delimiter = ft_strchr(args[i], '=');
		if (delimiter)
		{
			*delimiter = '\0';
			ms_setenv(envp, args[i], NULL);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}