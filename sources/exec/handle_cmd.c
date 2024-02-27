/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:37:01 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/27 13:46:58 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_prompt *prompt, t_child *childs, bool input_redir, int index_child)
{
	char **tab_cmd;

	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (3);
	else if (childs[index_child].pid == 0)
	{
		if (input_redir == true)
			dup2_read(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab, prompt->current_index, prompt->pos_after_token);
		if (tab_cmd == NULL)
			return (2);
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			return (1);
	}
	if (input_redir == true)
	{
		if (close(childs[index_child - 1].pipe_fd[READ]) == FAILURE)
			perror("close 5");
		if (close(childs[index_child - 1].pipe_fd[WRITE]) == FAILURE)
			perror("close 6");
	}
	return (SUCCESS);
}
