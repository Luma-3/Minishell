/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 11:56:56 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"
#include "display.h"
#include "ms_builtins.h"

volatile int	g_sigreceiver = 0;

static int	init_core_data(t_maindata *core_data, char *prompt)
{
	core_data->prompt = prompt;
	core_data->q_redir = ft_init_queue();
	core_data->q_kikidoc = ft_init_queue();
	core_data->q_pipe = ft_init_queue();
	if (core_data->q_redir == NULL || core_data->q_kikidoc == NULL
		|| core_data->q_pipe == NULL)
	{
		errno = ENOMEM;
		perror_switch(core_data->errors, "KikiShell", NULL);
		return (FAILURE);
	}
	core_data->root = NULL;
	core_data->is_pipeline = false;
	return (SUCCESS);
}

void	exec_process(t_maindata *core_data, char *input)
{
	ft_putchar_fd('\n', 1);
	if (init_core_data(core_data, input) == FAILURE)
		return ;
	if (parse_prompt(input, core_data, true) == FAILURE)
	{
		clear_ats(core_data, CORE_REDIR | CORE_ROOT | CORE_PROMPT | CORE_HEREDOC
			| CORE_PIPE);
		return ;
	}
	read_ats(core_data, core_data->root);
	ft_putchar_fd('\n', 1);
	clear_ats(core_data, CORE_REDIR | CORE_ROOT | CORE_PROMPT
		| CORE_HEREDOC | CORE_PIPE);
}

static void	read_input(t_maindata *core_data)
{
	char		*input;

	while (true)
	{
		core_data->save_stdin = dup(STDIN_FILENO);
		input = shell_prompt(core_data);
		if (g_sigreceiver == SIGQUIT)
			g_sigreceiver = 0;
		if (g_sigreceiver == SIGINT)
		{
			g_sigreceiver = 0;
			restore_stdin(core_data->errors, core_data->save_stdin);
			continue ;
		}
		else if (input == NULL)
		{
			display_msg(core_data, BYE_MSG);
			break ;
		}
		verif_add_history(input, core_data->history_fd);
		exec_process(core_data, input);
		restore_stdin(core_data->errors, core_data->save_stdin);
	}
	clear_ats(core_data, CORE_ALL);
}

int	main(int ac, char **av, char **envp)
{
	t_maindata	core_data;
	t_error		errors[__NB_ERRORS_];

	(void)av;
	if (ac != 1)
		print_error_why();
	if (init_shell(&core_data, errors, envp) == FAILURE)
		return (EXIT_FAILURE);
	read_input(&core_data);
	return (EXIT_SUCCESS);
}
