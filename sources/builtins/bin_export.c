/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 16:59:17 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"
#include "parser.h"

static bool	is_valid_name(char *name)
{
	while (name && *name)
	{
		if (valid_env_char(*name) == false)
			return (false);
		name++;
	}
	return (true);
}

int	ms_export(char **args, t_list **envp, t_error *errors)
{
	int		i;
	int		j;
	char	*name;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		name = ft_substr(args[i], 0, (size_t)j);
		if (name == NULL)
			return (ENOMEM);
		if (is_valid_name(name) == false)
		{
			errno = EINVID;
			ft_putstr_fd("export: ", STDERR_FILENO);
			perror_switch(errors, name);
			return (free(name), errno);
		}
		ms_setenv(envp, name, &args[i][j + 1]);
		free(name);
		i++;
	}
	return (EXIT_SUCCESS);
}
