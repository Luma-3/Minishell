/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:03:33 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/04 11:11:13 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"

static void	dup2_write_pipe(t_child *childs, int index_child)
{
	if (dup2(childs[index_child].pipe_fd[WRITE], STDOUT_FILENO) == FAILURE)
		perror("dup2 2");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 3");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 4");
}

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
		dup2_write_pipe(childs, index_child);
		if (input_redir == true)
			dup2_read_pipe(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab,
				prompt->current_index, prompt->pos_after_token - 1);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (is_builtins(tab_cmd[0]) == true)
		{
			if (exec_builtins(tab_cmd, prompt) == FAILURE)
				exit (EXIT_FAILURE);
			exit (EXIT_SUCCESS);
		}
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	if (input_redir)
		close_pipe(childs, index_child - 1);
	return (SUCCESS);
}

void	close_pipe(t_child *childs, int index_child)
{
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 5");
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 6");
}

void	dup2_read_pipe(t_child *childs, int index_child)
{
	if (close(childs[index_child].pipe_fd[WRITE]) == FAILURE)
		perror("close 1");
	if (dup2(childs[index_child].pipe_fd[READ], STDIN_FILENO) == FAILURE)
		perror("dup2 1");
	if (close(childs[index_child].pipe_fd[READ]) == FAILURE)
		perror("close 2");
}
