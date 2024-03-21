/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 09:36:57 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "redirection.h"
#include "ms_builtins.h"
#include <stdio.h>

int	open_all_redir(t_ats *ats, t_bin_tree *root)
{
	if (!root)
		return (SUCCESS);
	open_all_redir(ats, root->left);
	return (open_redir(ats, root));
}

int	open_pipe(t_ats *ats, t_bin_tree *root)
{
	int	*pipe_fd[2];
	int	nb_nodes;

	nb_nodes = 0;
	nb_nodes = count_nodes(root, nb_nodes);
	*pipe_fd = malloc(sizeof(int *) * nb_nodes);
	if (!pipe_fd)
		return (FAILURE);
	while (nb_nodes >= 0)
	{
		if (pipe(pipe_fd[nb_nodes]) == -1)
			return (FAILURE);
		nb_nodes--;
	}
	return (SUCCESS);
}