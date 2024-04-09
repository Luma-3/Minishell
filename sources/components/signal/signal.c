/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:03:56 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 17:32:22 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_sig.h"
#include "core_data.h"
#include "minishell.h"
#include "display.h"
#include <readline/readline.h>

extern volatile int	g_sigreceiver;

static void	sigint_handler(int sig)
{
	char	*uname;

	g_sigreceiver = sig;
	write(STDOUT_FILENO, "\n", 1);
	uname = get_uname();
	close(STDIN_FILENO);
	free(uname);
	rl_on_new_line();
}

static void	sigquit_handler(int sig)
{
	g_sigreceiver = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	init_signal(void)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}
