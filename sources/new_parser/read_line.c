/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/06 17:47:50 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int redir_type(const char *prompt, int index)
{
	if (prompt[index] == '<' && prompt[index + 1] != '<')
		return (REDIR_IN);
	else if (prompt[index] == '>' && prompt[index + 1] != '>')
		return (REDIR_OUT);
	else if (prompt[index] == '>' && prompt[index + 1] == '>')
		return (REDIR_OUT_APPEND);
	else if (prompt[index] == '<' && prompt[index + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (0);
}

int	take_redir(const char *prompt, t_queue *queue, int index_read)
{
	t_queue_redir	*data;
	int				i;

	i = 0;
	data = (t_queue_redir *)malloc(sizeof(t_queue_redir));
	if (!data)
		return (FAILURE);
	ft_enqueue(queue, data);
	data->type_redir = redir_type(prompt, index_read);
	if (data->type_redir > 2)
		index_read += 2;
	else
		index_read++;
	index_read = ft_skip_whitespaces(prompt, index_read);
	while (prompt[index_read + i] && ft_iswhitespace(prompt[index_read + i]) == false)
		i++;
	data->file_name = ft_strndup(&prompt[index_read], i);
	printf("file_name = %s\n", data->file_name);
	printf("type_redir = %d\n", data->type_redir);
	return (index_read + i);
}

static t_token *init_token_node(const char *cmd, int size_cmd, int nb_redir)
{
	t_token	*token;
	
	if (size_cmd == 0)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = ft_strndup(cmd, size_cmd);
	token->nb_redir = nb_redir;
	return (token);
}

int copy_cmd_token(t_ats *ats, int nb_redir, int index_read, int *index_copy)
{
	t_token		*data;
	
	data = init_token_node(&(ats->prompt[*index_copy]), index_read - *index_copy, nb_redir);
	if (data != NULL)
	{
		insert_node(&(ats->root), data, compare_token);
		*index_copy = index_read;
	}
	if (ats->prompt[index_read] == '\0')
	{
		return (index_read);
	}
	index_read = place_cursor_after_token(ats->prompt, index_read);
	data = init_token_node(&(ats->prompt[*index_copy]), index_read - *index_copy, 0);
	insert_node(&(ats->root), data, compare_token);
	*index_copy = index_read;
	return (index_read);
}

int    pipeline_is_solo(const char *prompt)
{
	int i;

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

int	copy_pipeline(t_ats *ats, int index_read, int *index_copy, int nb_redir)
{
	t_token	*data;
	
	while ((ats->prompt[index_read] && is_token(ats->prompt[index_read]) == false) || is_pipe(ats->prompt, index_read) == true)
	{
		index_read = skip_quote_parenthesis(ats->prompt, index_read);
		index_read++;
	}
	data = init_token_node(&(ats->prompt[*index_copy]), index_read - *index_copy, nb_redir);
	insert_node(&(ats->root), data, compare_token);
	*index_copy = index_read;
	return (index_read);
}

t_ats	*read_line(t_ats *ats)
{
	int 	index_copy;
	int		index_read;
	int		nb_redir;
	bool	is_solo;

	index_read = 0;
	nb_redir = 0;
	index_copy = 0;
	is_solo = pipeline_is_solo(ats->prompt);
	while (ats->prompt[index_read])
	{
		index_read = skip_quote_parenthesis(ats->prompt, index_read);
		if (redir_type(ats->prompt, index_read) != 0)
		{
			index_read = take_redir(ats->prompt, ats->queue, index_read);
			nb_redir++;
		}
		if (is_solo == false && is_pipe(ats->prompt, index_read) == true)
		{
			index_read = copy_pipeline(ats, index_read, &index_copy, nb_redir);
			nb_redir = 0;
		}
		else if (is_token(ats->prompt[index_read]) == true)
		{
			index_read = copy_cmd_token(ats, nb_redir, index_read, &index_copy);
			nb_redir = 0;
		}
		else
			index_read++;
	}
	copy_cmd_token(ats, nb_redir, index_read, &index_copy);
	return (ats);
}
//ls -l | grep "test" && echo "test" || echo "test"
