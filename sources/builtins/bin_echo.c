/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 14:28:36 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

static int	have_flag(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		if (arg[i][0] != '-')
			break ;
		j = 1;
		while (arg[i][j] == '\0')
		{
			if (arg[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static void	print_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	ms_echo(char **args, t_list **envp, t_error *errors)
{
	int	end_flag;

	(void)envp;
	(void)errors;
	end_flag = have_flag(args);
	print_arg(args + end_flag);
	if (end_flag > 0)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
