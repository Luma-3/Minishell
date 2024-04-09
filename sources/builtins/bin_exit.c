/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:27:38 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/09 12:18:23 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"
#include <signal.h>

static void	kill_all_processes(t_ats *node)
{
	if (node == NULL)
		return ;
	kill_all_processes(node->left);
	if (node->data->pid != -1)
		kill(node->data->pid, SIGINT);
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

int	ms_exit(char **args, t_list **envp, void *data)
{
	(void)envp;
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	kill_all_processes(((t_maindata *)data)->root);
	clear_ats((t_maindata *)data, CORE_ALL);
	if (args[1])
	{
		if (is_all_digit(args[1]) == false)
		{
			ft_putstr_fd("exit: \n", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(2);
		}
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(ft_atoi(args[1]));
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(0);
}
