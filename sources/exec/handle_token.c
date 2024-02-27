/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:07 by anthony           #+#    #+#             */
/*   Updated: 2024/02/26 15:13:38 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_token(t_prompt *prompt)
{
	prompt->pos_after_token = prompt->current_index;
	while (prompt->tab[prompt->pos_after_token])
	{
		if (ft_strncmp(prompt->tab[prompt->pos_after_token], "|", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_PIPE);
		}
		prompt->pos_after_token++;
	}
	return (T_NONE);
}
