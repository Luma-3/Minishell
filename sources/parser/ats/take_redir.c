/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:10:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 19:41:03 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static size_t	len_without_redir(const char *prompt)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		if (is_redir_type(prompt + i) != 0)
		{
			i += 2 - (is_redir_type(prompt + i) < 2);
			while (prompt[i] && ft_iswhitespace(prompt[i]) == true)
				i++;
			while (prompt[i] && ft_iswhitespace(prompt[i]) == false)
				i++;
		}
		len++;
		i++;
	}
	return (len);
}

static int	add_queue(t_ats *ats, const char *prompt, int redir_type,
							int size_prompt)
{
	t_queue_redir	*data;
	int				i;
	int				j;

	i = 0;
	data = (t_queue_redir *)malloc(sizeof(t_queue_redir));
	if (!data)
		return (FAILURE);
	data->type_redir = redir_type;
	ft_enqueue(ats->queue, data);
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

char	*take_redir(t_ats *ats, const char *prompt, int size_prompt,
					int *nb_redir)
{
	int		i;
	int		j;
	char	*new_prompt;

	new_prompt = ft_calloc(len_without_redir(prompt) + 1, sizeof(char));
	if (!new_prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[i] && i < size_prompt)
	{
		if (is_redir_type(prompt + i) > 0)
		{
			i += add_queue(ats, prompt, is_redir_type(prompt + i), size_prompt);
			nb_redir++;
		}
		else
		{
			new_prompt[j++] = prompt[i++];
		}
	}
	return (new_prompt);
}
