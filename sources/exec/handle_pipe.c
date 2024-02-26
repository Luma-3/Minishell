/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:03:33 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/26 19:36:21 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_read(t_child *childs, int index_child)
{
	if (dup2(childs[index_child].pipe_fd[READ], STDIN_FILENO) == FAILURE)
		perror("dup2 1");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 1");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 2");
}

static void	dup2_write(t_child *childs, int index_child)
{
	if (dup2(childs[index_child].pipe_fd[WRITE], STDOUT_FILENO) == FAILURE)
		perror("dup2 2");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 3");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 4");
}

int	handle_pipe(t_prompt *prompt, t_child *childs, bool input_redir, int index_child)
{
	char	**tab_cmd;

	input_redir = true;
	if (pipe(childs[index_child].pipe_fd) == FAILURE)
		return (FAILURE);
	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (FAILURE);
	else if (childs[index_child].pid == 0)
	{
		dup2_write(childs, index_child);
		if (input_redir == true && index_child > 0)
			dup2_read(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab, prompt->current_index, prompt->pos_after_token - 2);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
