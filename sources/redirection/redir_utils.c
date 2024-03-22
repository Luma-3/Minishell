/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:16:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 10:17:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	open_all_redir(t_queue *redir, t_queue *heredoc, t_bin_tree *root)
{
	if (!root)
		return (SUCCESS);
	open_all_redir(redir, heredoc, root->left);
	return (open_redir(redir, heredoc, root));
}
