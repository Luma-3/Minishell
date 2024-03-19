/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:58:32 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 11:20:30 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_token(t_ats *ats, t_bin_tree *node, pid_t *pid)
{
	int	status;
	int	final_status;

	if (waitpid(*pid, &status, 0) == -1)
	{
		status = errno;
	}
	final_status = status;
	if (status == 0 || ats->last_status == 0)
		final_status = 0;
	ats->last_status = status;
	if (ft_strncmp(node->data->cmd, "||", 2) == 0)
	{
		if (final_status == 0)
			return (STOP);
		return (CONTINUE);
	}
	else if (ft_strncmp(node->data->cmd, "&&", 2) == 0)
	{
		if (final_status == 0)
			return (CONTINUE);
		return (STOP);
	}
	return (CONTINUE);
}
