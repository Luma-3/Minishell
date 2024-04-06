/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:43 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/06 15:10:19 by anthony          ###   ########.fr       */
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

void	print_error_why(void)
{
	ft_putstr_fd("Why do you want to put arguments with KikiShell ?\n", 1);
	ft_putstr_fd("FLY, YOU FOOLS !!!\n", 1);
}
