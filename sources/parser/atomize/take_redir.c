/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:10:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/04 16:58:35 by jbrousse         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*new_prompt;
	char	quote;
	int		parenthesis;

	parenthesis = 0;
	new_prompt = ft_calloc(ft_strlen(prompt) + 1, sizeof(char));
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (prompt[i] && i < size_prompt)
	{
		if (is_quote(prompt[i]) == true && quote == '\0')
			quote = prompt[i];
		else if (is_quote(prompt[i]) == true && quote == prompt[i])
			quote = '\0';
		else if (prompt[i] == '(')
			parenthesis++;
		else if (prompt[i] == ')')
			parenthesis--;
		if (is_redir_type(prompt + i) > 0 && quote == '\0' && parenthesis == 0)
		{
			i += add_queue(ats, prompt + i, is_redir_type(prompt + i), size_prompt);
			*nb_redir += 1;
		}
		else if (i < size_prompt && prompt[i] != '\0')
			new_prompt[j++] = prompt[i++];
	}
	return (new_prompt);
}
