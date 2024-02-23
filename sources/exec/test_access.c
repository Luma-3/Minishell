/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:06:08 by anthony           #+#    #+#             */
/*   Updated: 2024/02/23 19:08:13 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_path_access(char *tab)
{
	if (access(tab, X_OK | F_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	test_exec_prog(char *tab)
{
	if (access(tab, X_OK | F_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}
