/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 17:34:30 by jbrousse         ###   ########.fr       */
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

	pipe_fd = malloc(sizeof(int *) * count_nodes(root));
	if (!pipe_fd)
		return (FAILURE);
	
}