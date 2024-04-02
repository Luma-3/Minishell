/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:27:38 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 13:25:26 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"

int	ms_exit(char **args, t_list **envp, t_error *errors)
{
	(void)envp;
	(void)args;
	(void)errors;
	// TODO
	exit(EXIT_SUCCESS);
}
