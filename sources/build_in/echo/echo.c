/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/13 14:12:25 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static int	verif_flag(const char *first_arg)
{
	if (ft_strncmp(first_arg, "-n", 2) == 0)
	{
		return (true);
	}
	return (false);
}

static void	print_args(const char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd((char *)args[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	echo(const char **args)
{
	bool	have_flag;

	have_flag = verif_flag(args[0]);
	if (have_flag)
	{
		print_args(args + 1);
	}
	else
	{
		print_args(args);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
