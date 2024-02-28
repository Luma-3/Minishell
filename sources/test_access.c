/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:06:08 by anthony           #+#    #+#             */
/*   Updated: 2024/02/28 15:01:04 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	test_path_access(char *tab)
{
	if (access(tab, F_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	test_exec_prog(char *tab)
{
	if (access(tab, X_OK) == 0)
		return (SUCCESS);
	return (FAILURE);
}
