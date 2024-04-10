/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/04/10 13:41:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	display_msg(t_maindata *core_data, char *msg)
{
	char	*command;

	command = ft_strdup(msg);
	if (command == NULL)
	{
		errno = ENOMEM;
		perror_switch(core_data->errors, "KikiShell", NULL);
		return ;
	}
	exec_process(core_data, command);
}

static char	*create_sh_prompt(char *path, char *uname, char *cwd, char *statu)
{
	char		*prompt;
	const char	*display[15] = {
		"\033[1;32m┏\033[0m"BG_BLACK_INV,
		BOLD_GREEN" ", uname, " 👾 "RESET,
		BG_BLACK, BOLD_BLUE" ", path, " "RESET,
		BG_BLACK_INV, BOLD_BLUE" ", cwd,
		" ", statu, RESET, NULL};

	prompt = assemble(display);
	return (prompt);
}

static void	free_params(char *cwd, char *path, int status_ret)
{
	if (!(status_ret & 0x01))
		free(cwd);
	if (!(status_ret & 0x02))
		free(path);
}

static char	*get_params_prompt(t_list *env, char *uname, int last_status,
	int status_ret)
{
	char	*cwd;
	char	*path;
	char	*status;
	char	*prompt;

	cwd = get_current_dir();
	if (cwd == NULL)
	{
		status_ret |= 0x01;
		cwd = "In the void!";
	}
	path = path_to_tilde(env);
	if (path == NULL)
	{
		status_ret |= 0x02;
		path = "I AM LOST!";
	}
	status = "😃 ";
	if (last_status != 0)
		status = "😡 ";
	if (uname == NULL)
		uname = "Kikishell";
	prompt = create_sh_prompt(path, uname, cwd, status);
	return (free_params(cwd, path, status_ret), prompt);
}

char	*shell_prompt(t_maindata *core_data)
{
	char	*input;
	char	*prompt;
	char	*line;

	line = PROMPT_SHELL;
	prompt = get_params_prompt(core_data->env, core_data->uname,
			core_data->last_status, 0);
	if (prompt != NULL)
		ft_putendl_fd(prompt, 1);
	else
		ft_putendl_fd("| Kikishell |", 1);
	free(prompt);
	input = readline(line);
	return (input);
}
