/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/06 10:54:35 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void	take_part_to_ats(const char *prompt, t_bin_tree **root, int start, int end)
{
	t_token	*data;
	
	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
		return ;
	data->cmd = ft_strndup(&prompt[start], end - start);
	insert_node(root, data, compare_token);
}

int	take_part_before_token(const char *prompt, t_bin_tree **root,
			int index_copy, int index_read)
{
	take_part_to_ats(prompt, root, index_copy, index_read);
	return (index_read);
}

int	take_token(const char *prompt, t_bin_tree **root, int index_read, int index_copy)
{	
	while (is_token(prompt[index_read]) == true)
		index_read++;
	take_part_to_ats(prompt, root, index_copy, index_read);
	return (index_read);
}

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
	while (ft_iswhitespace(prompt[index_read + i]) == false)
		i++;
	data->file_name = ft_strndup(&prompt[index_read], i);
	printf("file_name = %s\n", data->file_name);
	printf("type_redir = %d\n", data->type_redir);
	//TODO :  FIND KEY PROCESS
	return (index_read + i);
}

t_ats	*read_line(const char *prompt, t_ats *ats)
{
	int			index_copy;
	int			index_read;

	index_read = 0;
	index_copy = 0;
	while (prompt[index_read])
	{
		if (isquote_type(prompt[index_read]) == true)
			index_read = place_cursor_after_quote(prompt, index_read);
		if (redir_type(prompt, index_read) != 0)
			index_read = take_redir(prompt, ats->queue, index_read);
		if (is_parenthesis(prompt[index_read]) == true)
			index_read = place_cursor_after_parenthesis(prompt, index_read);
		else if (is_token(prompt[index_read]) == true)
		{
			index_copy = take_part_before_token(prompt, &(ats->root), index_copy, index_read);
			index_read = take_token(prompt, &(ats->root), index_read, index_copy);
			index_copy = index_read;
		}
		else
			index_read++;
	}
	take_part_to_ats(prompt, &(ats->root), index_copy, index_read);
	return (ats);
}
//ls -l | grep "test" && echo "test" || echo "test"