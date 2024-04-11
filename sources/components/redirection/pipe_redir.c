/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 14:12:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"
#include "parser.h"

void	handle_pipeline_redir(t_maindata *core_data)
{
	size_t			index;
	int				fd;
	t_redir_data	*node_redir;

	index = 0;
	while (true)
	{
		node_redir = (t_redir_data *)ft_peekat_queue(core_data->q_redir, index);
		if (!node_redir)
			break ;
		if (node_redir->type_redir == REDIR_OUT
			|| node_redir->type_redir == REDIR_OUT_APPEND)
		{
			fd = open(node_redir->filename, O_CREAT, 0644);
			if (fd == -1)
				perror("open");
			else
				close(fd);
		}
		index++;
	}
}
