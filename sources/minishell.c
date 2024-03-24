/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/24 12:40:30 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"

volatile int	g_sigreciever = 0;

void	init_ats(t_ats *ats, char *prompt, t_list *env)
{
	t_bin_tree	*root;

	root = NULL;
	ats->env = env;
	ats->prompt = prompt;
	ats->queue_redir = ft_init_queue();
	ats->queue_heredoc = ft_init_queue();
	ats->queue_pipe = ft_init_queue();
	ats->root = root;
	ats->last_status = 1;
}

void	process_input(t_ats *ats, t_list *env, char *input)
{
	ft_putchar_fd('\n', 1);
	init_ats(ats, input, env);
	ft_add_history(input, env);
	if (parse_ats(input, ats, true) == FAILURE)
		clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC
			| ATS_PIPE);
	read_ats(ats, ats->root);
	ft_putchar_fd('\n', 1);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC | ATS_PIPE);
}

void	read_input(t_list *env, t_error *errors)
{
	t_ats		ats;
	char		*prompt;
	char		*tmp_prompt;
	char		*input;

	prompt = NULL;
	ats.errors = errors;
	presentation_display(&ats, &env);
	while (true)
	{
		g_sigreciever = 0;
		tmp_prompt = handle_position(env, prompt, ats.last_status);
		if (tmp_prompt != NULL)
		{
			free(prompt);
			prompt = tmp_prompt;
		}
		ft_putendl_fd(prompt, 1);
		input = readline("\001\033[1;32m┗━━▶\002\033[0m ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
			process_input(&ats, env, input);
	}
	free(prompt);
	clear_ats(&ats, ATS_ENV);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;
	t_error	errors[__NB_ERRORS_];

	(void)av;
	__init_error__(errors);
	printf("\033]0;KikiShell\007");
	init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	if (env == NULL)
	{
		perror_switch(errors, "KikiShell");
		return (EXIT_FAILURE);
	}
	if (ft_create_history(env) == FAILURE)
	{
		perror_switch(errors, "KikiShell");
		return (EXIT_FAILURE);
	}
	read_input(env, errors);
	return (EXIT_SUCCESS);
}
