/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:07 by anthony           #+#    #+#             */
/*   Updated: 2024/02/27 23:13:04 by anthony          ###   ########.fr       */
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
		else if (ft_strncmp(prompt->tab[prompt->pos_after_token], "&&", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_AND);
		}
		else if (ft_strncmp(prompt->tab[prompt->pos_after_token], "||", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_OR);
		}
		prompt->pos_after_token++;
	}
	return (T_NONE);
}
