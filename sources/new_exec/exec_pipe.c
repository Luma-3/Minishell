/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:16:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 13:29:40 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "redirection.h"
#include "ms_builtins.h"
#include <stdio.h>

pid_t	exec_pipe()
{}

int	read_pipeline(t_ats *ats, t_bin_tree *root)
{
	int	count_pipe;

	read_inorder(ats, root, true);
	count_pipe = count_nodes(root, 0);
	
	
}

int read_inorder(t_ats *ats, t_bin_tree *root, bool is_redir)
{
	if (!root)
		return (SUCCESS);
	read_inorder(ats, root->left, is_redir);
	if (is_redir == true)
	{
		if (is_operator(root) == false)
			open_redir(ats, root);
	}
	else
		//exec
	read_inorder
	
}