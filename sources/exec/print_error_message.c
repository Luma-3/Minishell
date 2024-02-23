/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:43 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/23 13:48:48 by antgabri         ###   ########.fr       */
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
