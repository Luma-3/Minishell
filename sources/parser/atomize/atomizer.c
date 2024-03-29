/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomizer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 09:27:55 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	add_queue_pipe(t_queue *queue, int nb_pipe)
{
	t_queue_pipe	*data;

	data = malloc(sizeof(t_queue_pipe));
	if (data == NULL)
		return (FAILURE);
	data->index = nb_pipe;
	if (pipe(data->pipe_fd) == FAILURE)
	{
		free(data);
		return (FAILURE);
	}
	ft_enqueue(queue, data);
	return (SUCCESS);
}

static int	copy_cmd_pipe(t_maindata *ats, int i_copy, int i_read, int *nb_pipe)
{
	t_token	*data;

	data = copy_insert_node(ats, i_copy, i_read);
	if (data == NULL || ats->queue_pipe == NULL)
		return (FAILURE);
	data->require_wait = false;
	data->index = *nb_pipe;
	add_queue_pipe(ats->queue_pipe, *nb_pipe);
	(*nb_pipe)++;
	return (SUCCESS);
}

static int	atomize_pipeline(t_maindata *ats)
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
			if (copy_cmd_pipe(ats, i_copy, i_read, &nb_pipe) == FAILURE)
				return (FAILURE);
			i_copy = ++i_read;
		}
		else
			i_read++;
	}
	data = copy_insert_node(ats, i_copy, i_read);
	if (data == NULL)
		return (FAILURE);
	data->index = nb_pipe;
	return (SUCCESS);
}

int	atomize_prompt(t_maindata *ats)
{
	int		i_copy;
	int		i_read;

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
	if (copy_insert_node(ats, i_copy, i_read) == NULL)
		return (FAILURE);
	return (SUCCESS);
}
