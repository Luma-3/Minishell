/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:40:11 by jbrousse         ###   ########.fr       */
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
	core_data->queue_redir = ft_init_queue();
	core_data->queue_heredoc = ft_init_queue();
	core_data->queue_pipe = ft_init_queue();
	if (core_data->queue_redir == NULL || core_data->queue_heredoc == NULL
		|| core_data->queue_pipe == NULL)
	{
		errno = ENOMEM;
		perror_switch(core_data->errors, "KikiShell", NULL);
		return (FAILURE);
	}
	core_data->root = NULL;
	core_data->is_pipeline = false;
	return (SUCCESS);
}

char	*get_home(const char *uname)
{
	char	*home;

	home = ft_strjoin("/home/", uname);
	if (home == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (home);
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
	if (g_sigreceiver != SIGINT)
		ft_putchar_fd('\n', 1);
	clear_ats(core_data, CORE_REDIR | CORE_ROOT | CORE_PROMPT
		| CORE_HEREDOC | CORE_PIPE);
}

static void	read_input(t_maindata *core_data)
{
	char		*input;

	while (true)
	{
		core_data->stdin_fd = dup(STDIN_FILENO);
		input = shell_prompt(core_data);
		if (g_sigreceiver == SIGQUIT)
			g_sigreceiver = 0;
		if (g_sigreceiver == SIGINT)
		{
			g_sigreceiver = 0;
			dup2(core_data->stdin_fd, STDIN_FILENO);
			close(core_data->stdin_fd);
			continue ;
		}
		else if (input == NULL)
		{
			free(input);
			dup2(core_data->stdin_fd, STDIN_FILENO);
			(close(core_data->stdin_fd), close(core_data->history_fd));
			display_msg(core_data, BYE_MSG);
			break ;
		}
		ft_add_history(input, core_data->history_fd);
		exec_process(core_data, input);
		dup2(core_data->stdin_fd, STDIN_FILENO);
		close(core_data->stdin_fd);
	}
	clear_ats(core_data, CORE_UNAME | CORE_ENV | CORE_PATH);
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
