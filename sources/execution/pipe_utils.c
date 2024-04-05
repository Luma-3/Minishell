/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:16:43 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/05 15:32:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "parser.h"

void	close_all_pipes(t_maindata *core_data)
{
	t_queue_pipe	*data;

	while (true)
	{
		data = ft_dequeue(core_data->queue_pipe);
		if (data == NULL)
			break ;
		if (close(data->pipe_fd[READ]) == FAILURE)
		{
			perror_switch(core_data->errors, "close read all");
			free(data);
			return ;
		}
		if (close(data->pipe_fd[WRITE]) == FAILURE)
		{
			perror_switch(core_data->errors, "close write all");
			free(data);
			return ;
		}
		free(data);
	}
	return ;
}