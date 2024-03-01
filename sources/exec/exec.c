/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/01 15:33:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static void	dispatch_token(t_prompt *prompt,
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
		if (handle_std(prompt, childs, prompt->input_redir, index_child) == FAILURE)
			perror("minishell");
		prompt->input_redir = false;
	}
}

static t_child	*init_child(t_child *child, int nb_child)
{
	int	i;

	i = 0;
	child = malloc(sizeof(t_child) * (nb_child + 1));
	if (child == NULL)
		return (NULL);
	while (i < nb_child)
	{
		child[i].pid = 0;
		child[i].status = 0;
		child[i].pipe_fd[0] = 0;
		child[i].pipe_fd[1] = 1;
		i++;
	}
	child[i].pid = -255;
	return (child);
}

int	launch_child(t_prompt *prompt)
{
	int		token;
	int		index_child;
	static t_child	*childs;

	index_child = 0;
	childs = NULL;
	childs = init_child(childs, prompt->nb_cmd);
	prompt->input_redir = false;
	while (prompt->tab[prompt->current_index])
	{
		token = detect_token(prompt);
		// handle exit
		dispatch_token(prompt, childs, token, index_child);
		index_child++;
		prompt->current_index = prompt->pos_after_token;
	}
	wait_child(childs, prompt->nb_cmd);
	free(childs);
	return (SUCCESS);
}
