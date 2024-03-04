/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 11:08:52 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int	ms_export(const char *prompt, char **args, t_list **envp)
{
	int		i;
	int		j;
	char	*name;

	(void)prompt;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		name = ft_substr(args[i], 0, j);
		ms_setenv(envp, name, &args[i][j + 1]);
		i++;
	}
	return (EXIT_SUCCESS);
}
