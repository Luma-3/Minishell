/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 12:22:15 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skip_quote_parenthesis(const char *prompt, int index)
{
	if (is_quote_type(prompt[index]) == true)
		index = place_cursor_after_quote(prompt, index);
	if (is_parenthesis(prompt[index]) == true)
		index = place_cursor_after_parenthesis(prompt, index);
	return (index);
}

static int	take_redir(const char *prompt, t_queue *queue, int *i_read)
{
	t_queue_redir	*data;
	int				i;

	i = 0;
	data = (t_queue_redir *)malloc(sizeof(t_queue_redir));
	if (!data)
		return (FAILURE);
	ft_enqueue(queue, data);
	data->type_redir = is_redir_type(prompt, *i_read);
	if (data->type_redir > 2)
		*i_read += 2;
	else
		*i_read += 1;
	i_read = ft_skip_whitespaces(prompt, i_read);
	while (prompt[*i_read + i] && ft_iswhitespace(prompt[*i_read + i]) == false)
		i++;
	data->file_name = ft_strndup(&prompt[*i_read], i);
	i_read += i;
	return (1);
}

static int	pipeline_is_solo(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] || prompt[i] == '|')
	{
		i = skip_quote_parenthesis(prompt, i);
		if (is_token(prompt[i]) == true && is_pipe(prompt, i) == false)
			return (false);
		else
			i++;
	}
	if (prompt[i] == '\0')
		return (true);
	return (false);
}

t_ats	*create_ats(t_ats *ats)
{
	int		i_copy;
	int		i_read;
	int		nb_redir;
	bool	is_solo;

	i_read = 0;
	nb_redir = 0;
	i_copy = 0;
	is_solo = pipeline_is_solo(ats->prompt);
	while (ats->prompt[i_read])
	{
		i_read = skip_quote_parenthesis(ats->prompt, i_read);
		if (is_redir_type(ats->prompt, i_read) != 0)
			nb_redir += take_redir(ats->prompt, ats->queue, &i_read);
		if (is_solo == false && is_pipe(ats->prompt, i_read) == true)
			i_read = copy_pipeline(ats, i_read, &i_copy, &nb_redir);
		else if (is_token(ats->prompt[i_read]) == true)
			i_read = copy_cmd_token(ats, &nb_redir, i_read, &i_copy);
		else
			i_read++;
	}
	copy_cmd_token(ats, nb_redir, i_read, &i_copy);
	return (ats);
}
