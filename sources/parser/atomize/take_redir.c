/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:10:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/04 17:35:27 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	add_queue(t_maindata *ats, const char *prompt, int redir_type,
							int size_prompt)
{
	t_queue_redir	*data;
	int				i;
	int				j;

	i = 0;
	j = 0;
	data = (t_queue_redir *)malloc(sizeof(t_queue_redir));
	if (!data)
		return (FAILURE);
	if (!ats->queue_redir)
		return (free(data), FAILURE);
	data->type_redir = redir_type;
	ft_enqueue(ats->queue_redir, data);
	if (data->type_redir > 2)
		i += 2;
	else
		i++;
	i = ft_skip_whitespaces(prompt, i);
	while (prompt[i + j] && i + j < size_prompt
		&& ft_iswhitespace(prompt[i + j]) == false
		&& is_redir_type(prompt + i + j) == 0)
		j++;
	data->file_name = ft_strndup(&prompt[i], j);
	return (i + j);
}

char	*take_redir(t_maindata *ats, const char *prompt, int size_prompt,
					int *nb_redir)
{
	char	*new_prompt;
	int		i;
	int		j;
	int		parenthesis;
	char	quote;

	parenthesis = 0;
	new_prompt = ft_calloc(ft_strlen(prompt) + 1, sizeof(char));
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (prompt[i] && i < size_prompt)
	{
		if (is_quote(prompt[i]) == true)
			quote = check_quote(quote, prompt[i]);
		else if (prompt[i] == '(' || prompt[i] == ')')
			parenthesis += check_parenthesis(prompt[i]);
		if (is_redir_type(prompt + i) > 0 && quote == '\0' && parenthesis == 0)
		{
			i += add_queue(ats, prompt + i,
					is_redir_type(prompt + i), size_prompt);
			*nb_redir += 1;
		}
		else if (i < size_prompt && prompt[i] != '\0')
			new_prompt[j++] = prompt[i++];
	}
	return (new_prompt);
}
