/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:41:07 by anthony           #+#    #+#             */
/*   Updated: 2024/02/28 14:58:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	dispatch_token(t_prompt *prompt,
	t_child *childs, int token, int index_child)
{
	if (token == T_PIPE)
	{
		handle_pipe(prompt, childs, prompt->input_redir, index_child);
		prompt->input_redir = true;
	}
	else if (token == T_AND)
	{
		if (handle_and(prompt, childs,
				prompt->input_redir, index_child) == FAILURE)
			skip_next_cmd(prompt);
		prompt->input_redir = false;
	}
	else if (token == T_OR)
	{
		if (handle_or(prompt, childs,
				prompt->input_redir, index_child) == SUCCESS)
			skip_next_choice(prompt);
		prompt->input_redir = false;
	}
	else
	{
		if (handle_cmd(prompt, childs, prompt->input_redir, index_child) == FAILURE)
			perror("minishell");
		prompt->input_redir = false;
	}
}

int	detect_token(t_prompt *prompt)
{
	prompt->pos_after_token = prompt->current_index;
	while (prompt->tab[prompt->pos_after_token])
	{
		if (ft_strncmp(prompt->tab[prompt->pos_after_token], "|", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_PIPE);
		}
		else if (ft_strncmp(prompt->tab[prompt->pos_after_token], "&&", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_AND);
		}
		else if (ft_strncmp(prompt->tab[prompt->pos_after_token], "||", 2) == 0)
		{
			prompt->pos_after_token++;
			return (T_OR);
		}
		prompt->pos_after_token++;
	}
	return (T_NONE);
}
