/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/20 18:09:11 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	add_queue_pipe(t_queue *queue, int nb_pipe)
{
	t_queue_pipe	*data;

	data = malloc(sizeof(t_queue_pipe));
	if (pipe == NULL)
		return ;
	data->index = nb_pipe;
	if (pipe(data->pipe_fd) == FAILURE)
	{
		free(data);
		return (FAILURE);
	}
	ft_enqueue(&queue, data);
	return (SUCCESS);
}

static int	atomize_pipeline(t_ats *ats)
{
	int				i_read;
	int				i_copy;
	t_token			*data;
	int				nb_pipe;

	i_read = 0;
	i_copy = 0;
	nb_pipe = 0;
	while (ats->prompt[i_read])
	{
		i_read = skip_quote_parenthesis(ats->prompt, i_read);
		if (is_pipe(ats->prompt + i_read) == true)
		{
			data = copy_token(ats, ats->prompt + i_copy, i_read - i_copy);
			if (data == NULL)
				return (FAILURE);
			data->post_parser = true;
			data->require_wait = false;
			add_queue_pipe(ats->queue_pipe, nb_pipe++);
			insert_node(&(ats->root), data, compare_token);
			i_copy = ++i_read;
		}
		else
			i_read++;
	}
	data = copy_token(ats, ats->prompt + i_copy, i_read - i_copy);
	if (data == NULL)
		return (FAILURE);
	data->post_parser = true;
	return (insert_node(&(ats->root), data, compare_token), SUCCESS);
}

static int	atomize_prompt(t_ats *ats)
{
	int		i_copy;
	int		i_read;
	t_token	*data;

	i_copy = 0;
	i_read = 0;
	if (is_pipeline(ats->prompt) == true)
		return (atomize_pipeline(ats));
	while (ats->prompt[i_read])
	{
		i_read = skip_quote_parenthesis(ats->prompt, i_read);
		if (is_operator(ats->prompt + i_read) == true)
		{
			if (copy_cmd_operator(ats, &i_copy, &i_read) == FAILURE)
				return (FAILURE);
		}
		else
		{
			if (ats->prompt[i_read] != '\0')
				i_read++;
		}
	}
	data = copy_token(ats, ats->prompt + i_copy, i_read - i_copy);
	if (data == NULL)
		return (FAILURE);
	data->post_parser = true;
	insert_node(&(ats->root), data, compare_token);
	return (SUCCESS);
}

int	parse_ats(char *prompt, t_ats *ats, bool check_arg)
{
	(void)check_arg;
	// if (check_arg == true)
	// {
	// 	if (verif_arg(prompt) == FAILURE)
	// 		return (FAILURE);
	// 	handle_heredoc(prompt, ats);
	// }
	if (atomize_prompt(ats) == FAILURE)
		return (free(prompt), FAILURE);
	if (post_parser(ats->root) == FAILURE)
	{
		clear_tree(ats->root);
		ft_clear_queue(ats->queue_redir, free);
		return (free(prompt), FAILURE);
	}
	return (SUCCESS); // TODO : Free function to add !!!!!!!!!!!!!!!!!!!!!!!!!!
}
