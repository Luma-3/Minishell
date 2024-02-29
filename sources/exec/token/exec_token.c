/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:07 by anthony           #+#    #+#             */
/*   Updated: 2024/02/29 10:50:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_parent_process(t_child *childs, int index_child)
{
	waitpid(childs[index_child].pid, &childs[index_child].status, 0);
	if (childs[index_child].status != 0)
	{
		childs[index_child].status = -2;
		return (FAILURE);
	}
	else
		childs[index_child].status = -2;
	return (SUCCESS);
}

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
