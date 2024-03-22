/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 14:52:03 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"

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
	char		*input;
	t_ats		ats;
	char		*display_message;

	display_message = NULL;
	presentation_display(&ats, &env);
	while (true)
	{
		display_message = handle_position(env, display_message, ats.last_status);
		clear_ats(&ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC);
		ft_putstr_fd(display_message, 1);
		ft_putchar_fd('\n', 1);
		input = readline("\033[1;32m┗━━━▶\033[0m ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			ft_putchar_fd('\n', 1);
			init_ats(&ats, input, env);
			ft_add_history(input, env);
			parse_ats(input, &ats, true);
			read_ats(&ats, ats.root);
			(ft_putchar_fd('\n', 1), free(display_message));
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	ft_create_history(env);
	read_input(env);
	return (EXIT_SUCCESS);
}