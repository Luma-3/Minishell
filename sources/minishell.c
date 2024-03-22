/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 18:14:29 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"

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

void	read_input(t_list *env)
{
	t_ats		ats;
	char		*prompt;
	char		*tmp_prompt;
	char		*input;


	prompt = NULL;
	__init_error__(ats.errors);
	presentation_display(&ats, &env);
	while (true)
	{
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
		{
			ft_putchar_fd('\n', 1);
			init_ats(&ats, input, env);
			ft_add_history(input, env);
			parse_ats(input, &ats, true);
			read_ats(&ats, ats.root);
			ft_putchar_fd('\n', 1);
			clear_ats(&ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC | ATS_PIPE);
		}
		rl_on_new_line();
	}
	free(prompt);
	clear_ats(&ats, ATS_ENV | ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
		| ATS_REDIR | ATS_ROOT);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	printf("\033]0;KikiShell\007");
	init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	ft_create_history(env);
	read_input(env);
	return (EXIT_SUCCESS);
}
