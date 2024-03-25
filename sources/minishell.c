/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 21:01:35 by jbrousse         ###   ########.fr       */
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
		clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC
			| ATS_PIPE);
		return ;
	}
	read_ats(ats, ats->root);
	ft_putchar_fd('\n', 1);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC | ATS_PIPE);
}

void	read_input(t_list *env, t_error *errors)
{
	t_maindata	ats;
	char		*input;

	ats.errors = errors;
	presentation_display(&ats, env);
	while (true)
	{
		g_sigreciever = 0;
		ft_create_prompt(env, ats.last_status);
		input = readline("\001\033[1;32m┗━━▶\002\033[0m ");
		if (input == NULL)
		{
			free(input);
			goodbye_display(&ats, env);
			break ;
		}
		ft_add_history(input, env);
		exec_process(&ats, env, input);
	}
	ft_lstclear(&env, free);
}

int	init_shell(char **envp, int ac)
{
	t_list		*env;
	t_maindata	core_data;
	t_error		errors[__NB_ERRORS_];

	printf("\033]0;KikiShell\007");
	__init_error__(errors);
	init_signal();
	ft_bzero(&core_data, sizeof(t_maindata));
	env = env_to_lst(envp);
	if (ac != 1)
		return (print_error_why(env), EXIT_FAILURE); // TODO : check safe mode (anthony)
	if (ft_create_history(env) == FAILURE)
	{
		perror_switch(errors, "KikiShell");
		return (EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;

	init_shell();
	read_input(env, errors);
	return (EXIT_SUCCESS);
}
