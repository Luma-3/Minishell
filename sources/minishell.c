/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 17:04:00 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"

static void	init_ats(t_ats *ats, char *prompt, t_list *env)
{
	t_queue		*redir_queue;
	t_queue		*heredoc_queue;
	t_bin_tree	*root;

	root = NULL;
	redir_queue = ft_init_queue();
	heredoc_queue = ft_init_queue();
	ats->env = env;
	ats->prompt = prompt;
	ats->queue_redir = redir_queue;
	ats->queue_heredoc = heredoc_queue;
	ats->root = root;
	ats->last_status = 1;
}

void	read_input(t_list *env)
{
	char		*input;
	t_ats		ats;
	char		*display_message;

	display_message = NULL;
	while (true)
	{
		display_message = handle_position(env, display_message);
		input = readline(display_message);
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			init_ats(&ats, input, env);
			ft_add_history(input, env);
			parse_ats(input, &ats, true);
			read_ats(&ats, ats.root);
			clear_ats(&ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	printf("\033]0;MINISHELL\007");
	//init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	ft_create_history(env);
	//presentation_display(&env);
	read_input(env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL