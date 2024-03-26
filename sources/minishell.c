/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 14:54:59 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"
#include "display.h"

volatile int	g_sigreciever = 0;

int	init_ats(t_maindata *ats, char *prompt, t_list *env)
{
	t_ats	*root;

	root = NULL;
	ats->env = env;
	ats->prompt = prompt;
	ats->queue_redir = ft_init_queue();
	ats->queue_heredoc = ft_init_queue();
	ats->queue_pipe = ft_init_queue();
	if (ats->queue_redir == NULL || ats->queue_heredoc == NULL
		|| ats->queue_pipe == NULL)
	{
		errno = ENOMEM;
		perror_switch(ats->errors, "KikiShell");
		return (FAILURE);
	}
	ats->root = root;
	ats->last_status = 1;
	return (SUCCESS);
}

void	exec_process(t_maindata *ats, t_list *env, char *input)
{
	ft_putchar_fd('\n', 1);
	if (init_ats(ats, input, env) == FAILURE)
		return ;
	if (parse_ats(input, ats, true) == FAILURE)
	{
		clear_ats(ats, CORE_REDIR | CORE_ROOT | CORE_PROMPT | CORE_HEREDOC
			| CORE_PIPE);
		return ;
	}
	read_ats(ats, ats->root);
	ft_putchar_fd('\n', 1);
	clear_ats(ats, CORE_REDIR | CORE_ROOT | CORE_PROMPT | CORE_HEREDOC | CORE_PIPE);
}

void	read_input(t_maindata *core_data)
{
	char		*input;

	presentation_display(core_data, core_data->env);
	while (true)
	{
		g_sigreciever = 0;
		ft_create_prompt(core_data->env, core_data->last_status);
		input = readline("\001\033[1;32m┗━━▶\002\033[0m ");
		if (input == NULL)
		{
			free(input);
			goodbye_display(core_data, core_data->env);
			break ;
		}
		ft_add_history(input, core_data->history_fd);
		exec_process(core_data, core_data->env, input);
	}
	ft_lstclear(&(core_data->env), free);
}

int	main(int ac, char **av, char **envp)
{
	t_list		*env;
	t_maindata	core_data;
	t_error		errors[__NB_ERRORS_];

	(void)av;
	if (ac != 1)
		print_error_why();
	env = NULL;
	if (init_shell(&core_data, errors, env, envp) == FAILURE)
		return (EXIT_FAILURE);
	read_input(&core_data);
	return (EXIT_SUCCESS);
}
