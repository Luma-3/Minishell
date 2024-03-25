/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/25 10:27:41 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	presentation_display(t_ats *ats, t_list *env)
{
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border\
			Welcome in KIKISHELL");
	(init_ats(ats, command, env), parse_ats(command, ats, false));
	(read_ats(ats, ats->root), ft_putchar_fd('\n', 1));
}

void	goodbye_display(t_ats *ats, t_list *env)
{
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border\
			See you soon in KIKISHELL");
	clear_ats(ats, ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
	(init_ats(ats, command, env), parse_ats(command, ats, false));
	(read_ats(ats, ats->root), ft_putchar_fd('\n', 1));
	clear_ats(ats, ATS_ENV | ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
	return ;
}
char	*ft_create_prompt(t_list *env, int last_status)
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
	return (assemble(display));
}
