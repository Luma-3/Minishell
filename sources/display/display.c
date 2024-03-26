/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/26 18:42:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	display_msg(t_maindata *ats, t_list *env, char *msg)
{
	char	*command;

	command = ft_strdup(msg);
	if (command == NULL)
	{
		errno = ENOMEM;
		perror_switch(ats->errors, "KikiShell");
		return ;
	}
	exec_process(ats, env, command);
}

static void	create_sh_prompt(t_list *env, char *uname, int last_status)
{
	char	*display[15];

	display[0] = "\033[1;32m┏\033[0m"BG_BLACK_INV;
	display[1] = BOLD_GREEN" ";
	display[2] = uname;
	display[3] = " 😃 "RESET;
	display[4] = BG_BLACK;
	display[5] = BOLD_BLUE;
	display[6] = path_to_tilde(env);
	display[7] = " "RESET;
	display[8] = BG_BLACK_INV;
	display[9] = BOLD_BLUE" ";
	display[10] = get_current_dir();
	display[11] = " ";
	if (last_status == 0)
		display[12] = " ☀️  ";
	else
		display[12] = " 🌙 ";
	display[13] = RESET;
	display[14] = '\0';
	ft_putendl_fd(assemble(display), 1);
	free(display[6]);
	free(display[10]);
	return ;
}

static void	create_safe_prompt(t_list *env, char *uname)
{
	char	*display[7];

	display[0] = " ";
	display[1] = uname;
	display[2] = " @ ";
	display[3] = path_to_tilde(env);
	display[4] = " ";
	display[5] = "| SAFE MODE";
	display[6] = '\0';
	ft_putendl_fd(assemble(display), 1);
	free(display[3]);
	return ;
}
//😃🦆

char	*shell_prompt(t_maindata *core_data)
{
	char	*input;

	if (core_data->path != NULL)
	{
		create_safe_prompt(core_data->env, core_data->uname);
		input = readline("> ");
	}
	else
	{
		create_sh_prompt(core_data->env, core_data->uname,
			core_data->last_status);
		input = readline("\001\033[1;32m┗━━▶\002\033[0m ");
	}
	return (input);
}
