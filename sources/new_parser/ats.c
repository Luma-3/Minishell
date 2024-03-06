/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/05 16:39:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	create_ats(const char *prompt, t_ats *ats)
{
	read_line(prompt, ats);
}