/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:27:38 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 11:12:19 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "env.h"

int	ms_exit(const char *prompt, char **args, t_list **envp)
{
	(void)envp;
	(void)args;
	(void)prompt;
	// clear prompt | free prompt | etc ...
	exit(EXIT_SUCCESS);
}
