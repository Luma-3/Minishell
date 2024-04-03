/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:03:56 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/03 16:29:44 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_sig.h"
#include "core_data.h"
#include "minishell.h"
#include "display.h"
#include <readline/readline.h>

extern volatile int	g_sigreciever;

void	sigint_handler(int sig)
{
	char	*prompt;
	char	*uname;

	g_sigreciever = sig;
	uname = get_uname();
	prompt = create_sh_prompt(NULL, uname, 1);
	free(uname);
	printf("\n\n%s\n", prompt);
	free(prompt);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
