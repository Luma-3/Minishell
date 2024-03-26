/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:43 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/26 13:13:20 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "parser.h"
#include "ms_error.h"

void	print_error_message(void)
{
	perror(ERROR_FORMAT);
}

void	print_error_arg(char token)
{
	ft_putstr_fd("parse error near '", STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	print_error_arg_msg(void)
{
	ft_putstr_fd("kikishell: syntax error near", STDERR_FILENO);
	ft_putstr_fd("unexpected token `", STDERR_FILENO);
}

void	print_error_display(void)
{
	printf("minishell: toilet command not found\n");
	printf("You can install it with 'sudo apt install toilet'\n");
	printf("Restart minishell and now you have a beautiful display\n");
}

void	print_error_why(t_list *env)
{
	t_ats	ats;
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border WHY ?????");
	if (command == NULL)
	{
		errno = ENOMEM;
		ft_perror(ats.errors, "KikiShell");
		return ;
	}
	init_ats(&ats, command, env);
	if (parse_ats(command, &ats, true) == FAILURE)
	{
		clear_ats(&ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC
			| ATS_PIPE);
		return ;
	}
	read_ats(&ats, ats.root);
	ft_putstr_fd("Why do you want to put arguments with KikiShell ?\n", 1);
	ft_putstr_fd("FLY, YOU FOOLS !!!\n", 1);
	clear_ats(&ats, ATS_ENV | ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
			| ATS_REDIR | ATS_ROOT);
}
