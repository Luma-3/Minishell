/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:04 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 17:26:55 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"


int is_pipe(const char *prompt, int index)
{
	if (prompt[index] == '|' && prompt[index + 1] != '|')
		return (true);
	return (false);
}

static int is_token(char token)
{
	if (token == '|' || token == '&')
		return (true);
	return (false);
}

void	copy_token(const char *prompt, t_bin_tree **root, int start, int end)
{
	t_token	*data;
	
	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
		return ;
	data->cmd = ft_strndup(&prompt[start], end - start);
	insert_node(root, (t_tree_data){.token = data}, compare_token);
}

t_bin_tree	*read_line(const char *prompt, int *index_read)
{
	int			index_copy;
	t_bin_tree	*root;

	index_copy = *index_read;
	root = NULL;
	while (prompt[*index_read])
	{
		//printf("index_read = %d\n", *index_read);
		if (isquote_type(prompt[*index_read]) == true)
			*index_read = place_cursor_after_quote(prompt, *index_read);
		if (is_token(prompt[*index_read]) == true)
		{
			copy_token(prompt, &root, index_copy, *index_read);
			index_copy = *index_read;
			// if (is_pipe(prompt, index_copy) == true)
			// 	return (root);
			while (is_token(prompt[*index_read]) == true)
				*index_read += 1;
			copy_token(prompt, &root, index_copy, *index_read);
			index_copy = *index_read;
		}
		*index_read += 1;
	}
	copy_token(prompt, &root, index_copy, *index_read);
	return (root);
}
//ls -l | grep "test" && echo "test" || echo "test"