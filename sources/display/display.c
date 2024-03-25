/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/25 12:19:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	presentation_display(t_ats *ats, t_list *env)
{
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border\
			Welcome in KIKISHELL");
	if (command == NULL)
	{
		errno = ENOMEM;
		perror_switch(ats->errors, "KikiShell");
		return ;
	}
	init_ats(ats, command, env);
	if (parse_ats(command, ats, true) == FAILURE)
	{
		clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC
			| ATS_PIPE);
		return ;
	}
	(read_ats(ats, ats->root), ft_putchar_fd('\n', 1));
}

void	goodbye_display(t_ats *ats, t_list *env)
{
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border\
			See you soon in KIKISHELL");
	if (command == NULL)
	{
		errno = ENOMEM;
		perror_switch(ats->errors, "KikiShell");
		return ;
	}
	clear_ats(ats, ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
	init_ats(ats, command, env);
	if (parse_ats(command, ats, true) == FAILURE)
	{
		clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC
			| ATS_PIPE);
		return ;
	}
	read_ats(ats, ats->root);
	ft_putchar_fd('\n', 1);
	clear_ats(ats, ATS_ENV | ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
	return ;
}

void	ft_create_prompt(t_list *env, int last_status)
{
	char	*display[20];

	display[0] = "\033[1;32m┏\033[0m"BG_BLACK_INV;
	display[1] = BOLD_GREEN" ";
	display[2] = ms_getenv(env, "LOGNAME");
	display[3] = " 😃 "RESET;
	display[4] = BG_BLACK;
	display[5] = BOLD_BLUE;
	display[6] = path_to_tilde(env);
	display[7] = " "RESET;
	display[8] = BG_BLACK_INV;
	display[9] = BOLD_BLUE" ";
	display[10] = ft_get_chdir();
	display[11] = " ";
	if (last_status == 0)
		display[12] =" ☀️ ";
	else
		display[12] =" 🌙 ";
	display[13] = RESET;
	display[14] = '\0';
	assemble(display);
	return ;
}
