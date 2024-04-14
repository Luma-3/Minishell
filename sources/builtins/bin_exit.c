/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:27:38 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 15:15:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"
#include <signal.h>
#include "display.h"
#include <limits.h>

static void	kill_all_processes(t_ast *node)
{
	if (node == NULL)
		return ;
	kill_all_processes(node->left);
	if (node->data->pid != -1)
		kill(node->data->pid, SIGCHLD);
	waitpid(node->data->pid, NULL, 0);
	kill_all_processes(node->right);
}

static bool	is_all_digit(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

static int	clear_kikishell(t_maindata *core)
{
	int	ret;

	kill_all_processes(core->root);
	ret = core->last_status;
	clear_ats(core, CORE_REDIR | CORE_ROOT | CORE_PROMPT
		| CORE_HEREDOC | CORE_PIPE);
	display_msg(core, BYE_MSG);
	clear_ats(core, CORE_ALL);
	return (ret);
}

static unsigned long	str_to_ul(const char *str)
{
	unsigned long	ret;

	ret = 0;
	while (*str)
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

int	ms_exit(char **args, t_list **envp, void *data)
{
	unsigned long	ret;
	t_maindata		*core;

	(void)envp;
	core = (t_maindata *)data;
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = clear_kikishell(core);
	if (args[1])
	{
		if (is_all_digit(args[1]) == false)
			print_error_exit(args);
		ret = str_to_ul(args[1]);
		if (ret > UINT_MAX)
			print_error_exit(args);
		ft_rm_split(args);
		exit((unsigned int)ret);
	}
	ft_rm_split(args);
	exit((unsigned int)ret);
}
