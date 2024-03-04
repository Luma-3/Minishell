/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:36 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 11:09:57 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // TODO TRIER LES INCLUDES
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
}

int	exec_builtins(char **tab_cmd, t_prompt *prompt_struct)
{
	t_builtin	builtins[NB_BUILTINS];
	int			i;

	i = 0;
	init_builtins(builtins);
	while (i < NB_BUILTINS)
	{
		if (ft_strncmp(builtins[i].name, tab_cmd[0],
				ft_strlen(tab_cmd[0])) == 0)
		{
			builtins[i].func(prompt_struct->prompt,
				tab_cmd, prompt_struct->env);
			ft_rm_split(tab_cmd);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	ft_rm_split(tab_cmd);
	return (EXIT_FAILURE);
}

int	is_builtins(const char *cmd)
{
	t_builtin	builtins[NB_BUILTINS];
	int			i;

	i = 0;
	init_builtins(builtins);
	while (i < NB_BUILTINS)
	{
		if (ft_strncmp(builtins[i].name, cmd, ft_strlen(cmd)) == 0)
			return (true);
		i++;
	}
	return (false);
}

