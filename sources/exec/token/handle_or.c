/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:02:54 by anthony           #+#    #+#             */
/*   Updated: 2024/03/01 10:39:38 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ms_builtins.h"

int	skip_next_choice(t_prompt *prompt)
{
	while (prompt->tab[prompt->pos_after_token] != NULL)
	{
		if (prompt->tab[prompt->pos_after_token][0] == '&' &&
			prompt->tab[prompt->pos_after_token][1] == '&')
		{
			prompt->pos_after_token++;
			return (SUCCESS);
		}
		prompt->pos_after_token++;
	}
	return (FAILURE);
}

int	handle_or(t_prompt *prompt, t_child *childs,
	bool input_redir, int index_child)
{
	char	**tab_cmd;

	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (FAILURE);
	else if (childs[index_child].pid == 0)
	{
		if (input_redir == true)
			dup2_read_pipe(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab,
				prompt->current_index, prompt->pos_after_token - 1);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (is_builtins(tab_cmd[0]) == true)
			return (exec_builtins(tab_cmd, prompt));
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			exit (EXIT_FAILURE);
	}
	if (input_redir)
		close_pipe(childs, index_child - 1);
	return (handle_parent_process(childs, index_child));
}
