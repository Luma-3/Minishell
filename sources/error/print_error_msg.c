/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:43 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/25 11:11:26 by jbrousse         ###   ########.fr       */
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

void	print_error_display(void)
{
	printf("minishell: toilet command not found\n");
	printf("You can install it with 'sudo apt install toilet'\n");
	printf("Restart minishell and now you have a beautiful display\n");
}

int	wexit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

void	print_error_why(t_list *env)
{
	t_ats	ats;
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border WHY ?????");
	init_ats(&ats, command, env);
	parse_ats(command, &ats, false);
	read_ats(&ats, ats.root);
	ft_putstr_fd("Why do you want to put arguments with KikiShell ?\n", 1);
	ft_putstr_fd("FLY, YOU FOOLS !!!\n", 1);
	clear_ats(&ats, ATS_ENV | ATS_HEREDOC | ATS_PIPE | ATS_PROMPT
			| ATS_REDIR | ATS_ROOT);
}
