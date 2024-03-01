/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:03:56 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 15:53:56 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_sig.h"
#include "core_data.h"

void sigint_handler(int sig)
{
	static t_child *childs;
	int i;

	
	i = 0;
	if (childs != NULL && sig == SIGINT)
	{
		while (childs[i].pid != -255)
		{
			if (childs[i].pid != 0)
				kill(childs[i].pid, SIGKILL);
		}
	}
}

void init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
