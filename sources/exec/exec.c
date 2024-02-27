/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/27 14:43:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_child(t_prompt *prompt)
{
	int		token;
	int		index_child;
	bool	input_redir;
	t_child	*childs;

	input_redir = false;
	index_child = 0;
	childs = NULL;
	childs = init_child(childs, prompt->nb_cmd);
	while (prompt->tab[prompt->current_index])
	{
		token = detect_token(prompt);
		if (token == T_PIPE)
		{
			handle_pipe(prompt, childs, input_redir, index_child);
			input_redir = true;
		}
		else
		{
			handle_cmd(prompt, childs, input_redir, index_child);
			input_redir = false;
		}
		index_child++;
		prompt->current_index = prompt->pos_after_token;
	}
	wait_child(childs, prompt->nb_cmd);
	return (SUCCESS);
}
