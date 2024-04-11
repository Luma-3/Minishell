/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:03:56 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 18:14:38 by jbrousse         ###   ########.fr       */
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
	g_sigreceiver = sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

static void	sigquit_handler(int sig)
{
	g_sigreceiver = sig;
	printf("\033[2D\033[0K");
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal(void)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}
