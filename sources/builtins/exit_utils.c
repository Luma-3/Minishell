/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:09:54 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 15:10:58 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

void	print_error_exit(char **args)
{
	printf("exit: %s: numeric argument required\n", args[1]);
	ft_rm_split(args);
	exit(2);
}
