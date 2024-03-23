/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:03:56 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/23 23:25:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_sig.h"
#include "core_data.h"

// void	sigint_handler(int sig)
// {
	// TODO : handle SIGINT
	// Piste : au vue du fait que ai pas le droit de recuperer d'info sur le pid.
	// je oeu changer la valeur de la variable globale volatile sigint.
	// puis lors du wait dans la PARTE Exec il faudre while(true) en waitpid avec un macro WNOHANG
// }

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, sigint_handler);
}

