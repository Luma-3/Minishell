/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:37:01 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/27 16:30:46 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_prompt *prompt, t_child *childs, bool input_redir, int index_child)
{
	char **tab_cmd;

	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (FAILURE);
	else if (childs[index_child].pid == 0)
	{
		if (input_redir == true)
			dup2_read(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab, prompt->current_index, prompt->pos_after_token);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			return (FAILURE);
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
