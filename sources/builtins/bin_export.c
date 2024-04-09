/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 11:08:58 by jbrousse         ###   ########.fr       */
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

int	ms_export(char **args, t_list **envp, void *data)
{
	int		i;
	int		j;
	int		ret;
	char	*name;
	char	*value;

	i = 1;
	ret = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (j == 0)
			name = ft_strdup(args[i]);
		else
			name = ft_substr(args[i], 0, (size_t)j);
		if (name == NULL)
			return (ENOMEM);
		if (is_valid_name(name) == false)
		{
			errno = EINVID;
			ft_putstr_fd("Kikishell: export: '", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			perror_switch((t_error *)data, "'");
			free(name);
			ret = 1;
			i++;
			continue ;
		}
		value = ft_substr(args[i], (size_t)j + 1, ft_strlen(args[i]) - j - 1);
		ms_setenv(envp, name, value);
		free(value);
		free(name);
		i++;
	}
	return (ret);
}
