/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:10:20 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 12:00:34 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

bool	verif_filename(char *filename, t_error *errors)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (is_quote(filename[i]) == true)
			i = skip_quote_parenthesis(filename, i);
		if (filename[i] == '&' || filename[i] == '|' || filename[i] == '(')
		{
			errno = ESYNTAX;
			perror_switch(errors, "KikiShell", &filename[i]);
			return (false);
		}
		if (filename[i] != '\0')
			i++;
	}
	return (true);
}

static int	take_filename(t_queue_redir *data, const char *prompt,
	t_error *errors)
{
	int		i;
	char	*name;

	i = 0;
	while (prompt[i] && ft_iswhitespace(prompt[i]) == false
		&& is_redir_type(prompt + i) == 0)
	{
		if (is_quote(prompt[i]) == true)
			i = skip_quote_parenthesis(prompt, i);
		else
			i++;
	}
	name = ft_strndup(prompt, (size_t)i);
	if (name == NULL)
		return (FAILURE);
	if (verif_filename(name, errors) == false)
		return (FAILURE);
	data->file_name = clean_quote(name);
	free(name);
	if (data->file_name == NULL)
		return (FAILURE);
	return (i);
}

static int	add_queue(t_maindata *core_data, const char *prompt, int redir_type,
	int *i)
{
	t_queue_redir	*data;
	int				redir_len;
	int				len_name;

	data = (t_queue_redir *)malloc(sizeof(t_queue_redir));
	if (!data)
		return (FAILURE);
	if (!core_data->queue_redir)
		return (free(data), FAILURE);
	data->type_redir = redir_type;
	ft_enqueue(core_data->queue_redir, data);
	if (data->type_redir > 2)
		redir_len = 2;
	else
		redir_len = 1;
	redir_len = ft_skip_whitespaces(prompt, redir_len);
	len_name = take_filename(data, prompt + redir_len, core_data->errors);
	if (len_name == FAILURE)
		return (FAILURE);
	*i += len_name + redir_len;
	return (SUCCESS);
}

static void	check_quote_parenthesis(const char c, char *quote, int *parenthesis)
{
	if (is_quote(c) == true)
		*quote = check_quote(*quote, c);
	else if (c == '(' || c == ')')
		*parenthesis += check_parenthesis(c);
}

char	*take_redir(t_maindata *ats, const char *prompt, int *nb_redir)
{
	char	*new_prompt;
	int		i;
	int		j;
	int		parenthesis;
	char	quote;

	parenthesis = 0;
	i = 0;
	j = 0;
	quote = '\0';
	new_prompt = ft_calloc(ft_strlen(prompt) + 1, sizeof(char));
	while (new_prompt && ft_strlen(prompt) > (size_t)i && prompt[i])
	{
		check_quote_parenthesis(prompt[i], &quote, &parenthesis);
		if (is_redir_type(prompt + i) > 0 && quote == '\0' && parenthesis == 0)
		{
			if (add_queue(ats, prompt + i, is_redir_type(prompt + i), &i)
				== FAILURE)
				return (free(new_prompt), NULL);
			*nb_redir += 1;
		}
		else if (prompt[i] != '\0')
			new_prompt[j++] = prompt[i++];
	}
	return (new_prompt);
}
