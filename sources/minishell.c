/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/24 17:54:03 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"
#include "display.h"

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

static void	exec_process(t_ats *ats, t_list *env, char *input )
{
	clear_ats(ats, ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
	ft_putchar_fd('\n', 1);
	init_ats(ats, input, env);
	parse_ats(input, ats, true);
	read_ats(ats, ats->root);
	ft_add_history(input, env);
	ft_putchar_fd('\n', 1);
	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC | ATS_PIPE);
}

void	read_input(t_list *env)
{
	t_ats		ats;
	char		*prompt;
	char		*input;

	prompt = NULL;
	(__init_error__(ats.errors), presentation_display(&ats, env));
	while (true)
	{
		prompt = display_prompt(&ats, env, prompt);
		input = readline("\001\033[1;32m┗━━▶\002\033[0m ");
		if (input == NULL)
		{
			free(input);
			free(prompt);
			goodbye_display(&ats, env);
			break ;
		}
		exec_process(&ats, env, input);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;
	t_ats	ats;

	(void)av;
	printf("\033]0;KikiShell\007");
	init_signal();
	env = copy_env(envp);
	if (ac != 1)
		return (print_error_why(&ats, env), EXIT_FAILURE);
	ft_create_history(env);
	read_input(env);
	return (EXIT_SUCCESS);
}
