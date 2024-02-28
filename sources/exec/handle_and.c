/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:07:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/28 11:47:02 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_next_cmd(t_prompt *prompt)
{
	while (prompt->tab[prompt->pos_after_token] != NULL)
	{
		if (prompt->tab[prompt->pos_after_token][0] == '|' &&
			prompt->tab[prompt->pos_after_token][1] == '|')
		{
			prompt->pos_after_token++;
			return (SUCCESS);
		}
		prompt->pos_after_token++;
	}
	return (FAILURE);
}

int	handle_parent_process(t_child *childs, int index_child)
{
	waitpid(childs[index_child].pid, &childs[index_child].status, 0);
	if (childs[index_child].status != 0)
	{
		childs[index_child].status = -2;
		return (FAILURE);
	}
	else
		childs[index_child].status = -2;
	return (SUCCESS);
}

int	handle_and(t_prompt *prompt, t_child *childs,
	bool input_redir, int index_child)
{
	char	**tab_cmd;

	childs[index_child].pid = fork();
	if (childs[index_child].pid < 0)
		return (FAILURE);
	else if (childs[index_child].pid == 0)
	{
		if (input_redir == true)
			dup2_read(childs, index_child - 1);
		tab_cmd = ft_copy_tab(prompt->tab,
				prompt->current_index, prompt->pos_after_token - 1);
		if (tab_cmd == NULL)
			return (FAILURE);
		if (exec_command(tab_cmd, prompt->env) == FAILURE)
			exit (FAILURE);
		exit (SUCCESS);
	}
	return (handle_parent_process(childs, index_child));
}
