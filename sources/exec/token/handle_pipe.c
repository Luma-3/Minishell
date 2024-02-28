/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:03:33 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/28 12:55:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_pipe(t_prompt *prompt, t_child *childs,
	bool input_redir, int index_child)
{
	char	**tab_cmd;

	if (pipe(childs[index_child].pipe_fd) == FAILURE)
		return (FAILURE);
	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (FAILURE);
	else if (childs[index_child].pid == 0)
	{
		dup2_write(childs, index_child);
		if (input_redir == true)
			dup2_read(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab,
				prompt->current_index, prompt->pos_after_token - 1);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
