/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:43 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/26 10:50:25 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(void)
{
	perror(ERROR_FORMAT);
}

void	print_error_arg(char token)
{
	printf("parse error near '%c'\n", token);
}

void	print_error_display(void)
{
	printf("minishell: toilet command not found\n");
	printf("You can install it with 'sudo apt install toilet'\n");
	printf("Restart minishell and now you have a beautiful display\n");
}
