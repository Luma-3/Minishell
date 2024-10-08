/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:30:08 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_builtins.h"

static void	init_builtins(t_builtin *builtins)
{
	builtins[0] = (t_builtin){"echo", ms_echo};
	builtins[1] = (t_builtin){"cd", ms_cd};
	builtins[2] = (t_builtin){"pwd", ms_pwd};
	builtins[3] = (t_builtin){"export", ms_export};
	builtins[4] = (t_builtin){"unset", ms_unset};
	builtins[5] = (t_builtin){"env", ms_env};
	builtins[6] = (t_builtin){"exit", ms_exit};
	builtins[7] = (t_builtin){"history", ms_history};
}

int	chr_exec_bt(const char **tab_cmd, t_list **env, t_core *core_data)
{
	t_builtin	builtins[NB_BUILTINS];
	int			i;
	int			ret;

	i = 0;
	init_builtins(builtins);
	while (i < NB_BUILTINS)
	{
		if (ft_strncmp(builtins[i].name, tab_cmd[0],
				ft_strlen(tab_cmd[0])) == 0)
		{
			if (ft_strncmp(builtins[i].name, "exit", 4) == 0 || ft_strncmp(
					builtins[i].name, "history", 7) == 0)
				ret = builtins[i].func((char **)tab_cmd, env, core_data);
			else
				ret = builtins[i].func((char **)tab_cmd, env,
						core_data->errors);
			return (ret);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

bool	is_builtin(const char *cmd)
{
	t_builtin	builtins[NB_BUILTINS];
	int			i;

	i = 0;
	if (cmd == NULL)
		return (false);
	init_builtins(builtins);
	while (i < NB_BUILTINS)
	{
		if (ft_strncmp(builtins[i].name, cmd, ft_strlen(cmd)) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
