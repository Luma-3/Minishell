/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 12:10:05 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // TODO TRIER LES INCLUDES
#include "ms_builtins.h"

static void init_builtins(t_builtin *builtins)
{
	builtins[0] = (t_builtin){"echo", ms_echo};
	builtins[1] = (t_builtin){"cd", ms_cd};
	builtins[2] = (t_builtin){"pwd", ms_pwd};
	builtins[3] = (t_builtin){"export", ms_export};
	builtins[4] = (t_builtin){"unset", ms_unset};
	builtins[5] = (t_builtin){"env", ms_env};
	builtins[6] = (t_builtin){"exit", ms_exit};
	builtins[7] = (t_builtin){NULL, NULL};
}

int exec_builtins(const char **tab_cmd, t_prompt *prompt_struct)
{
	t_builtin	builtins[NB_BUILTINS + 1];
	int			i;

	i = 0;
	init_builtins(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins[i].name, tab_cmd[0]) == 0)
			return (builtins[i].func(prompt_struct->prompt, tab_cmd, prompt_struct->env));
		i++;
	}
	return (EXIT_FAILURE);
}

int is_builtins(const char *cmd)
{
	t_builtin	builtins[NB_BUILTINS + 1];
	int 		i;

	i = 0;
	init_builtins(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins->name, cmd) == 0)
			return (true);
		i++;
	}
	return (false);
}

