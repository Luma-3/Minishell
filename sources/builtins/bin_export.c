/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 15:04:08 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"
#include "parser.h"

static bool	is_valid_name(char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if (i == 0 && ft_isdigit(name[i]))
			return (false);
		if (valid_env_char(name[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

char	*get_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i == 0)
		return (ft_strdup(arg));
	return (ft_substr(arg, 0, i));
}

char	*get_value(char *arg)
{
	char	*value;
	char	*start_value;

	start_value = ft_strchr(arg, '=');
	if (start_value == NULL)
		return (ft_strdup(""));
	value = ft_strndup(start_value + 1, ft_strlen(start_value));
	return (value);
}

static int	export_var(char *arg, char *name, t_list **envp)
{
	char	*value;
	int		ret;

	value = get_value(arg);
	ret = ms_setenv(envp, name, value);
	free(value);
	free(name);
	return (ret);
}

int	ms_export(char **args, t_list **envp, void *data)
{
	int		i;
	int		ret;
	char	*name;

	i = 1;
	ret = 0;
	(void)data;
	while (args[i])
	{
		name = get_name(args[i]);
		if (name == NULL)
			return (errno);
		if (is_valid_name(name) == false)
		{
			printf("Kikishell: export: '%s': not a valid identifier\n", args[i]);
			(free(name), ret = 1);
		}
		else
			ret = export_var(args[i], name, envp);
		i++;
	}
	return (ret);
}
