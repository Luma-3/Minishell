/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats_copy_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:17:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/09 22:27:23 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*copy_whitout_parenthesis(const char *cmd, int size_cmd)
{
	char	*new_cmd;
	char	*tmp;
	int		i;

	new_cmd = ft_strndup(cmd, size_cmd);
	i = ft_skip_whitespaces(new_cmd, 0);
	if (new_cmd[i] != '(')
		return (new_cmd);
	tmp = ft_strtrim(new_cmd, " \t\n\v\f\r");
	free(new_cmd);
	new_cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
	free(tmp);
	return (new_cmd);
}

static t_token	*init_node(const char *cmd, int size_cmd, int nb_redir,
							bool post_parser)
{
	t_token	*token;

	if (size_cmd == 0)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->is_subshell = false;
	if (is_subshell(cmd, size_cmd) == true)
		token->is_subshell = true;
	token->cmd = copy_whitout_parenthesis(cmd, size_cmd);
	token->nb_redir = nb_redir;
	token->post_parser = post_parser;
	token->argv = NULL;
	token->last_cmd = false;
	return (token);
}

int	copy_last_cmd(t_ats *ats, int *nb_redir, int i_read, int *i_copy)
{
	t_token		*data;

	data = init_node(&(ats->prompt[*i_copy]), i_read - *i_copy,
			*nb_redir, true);
	data->last_cmd = true;
	if (data != NULL)
	{
		insert_node(&(ats->root), data, compare_token);
		*i_copy = i_read;
	}
	return (i_read);
}

int	copy_pipeline(t_ats *ats, int i_read, int *i_copy, int *nb_redir)
{
	t_token	*data;

	while ((ats->prompt[i_read] && is_token(ats->prompt[i_read]) == false)
		|| is_pipe(ats->prompt, i_read) == true)
	{
		i_read = skip_quote_parenthesis(ats->prompt, i_read);
		i_read++;
	}
	data = init_node(&(ats->prompt[*i_copy]), i_read - *i_copy, *nb_redir,
			false);
	data->is_subshell = true;
	if (data == NULL)
		return (FAILURE);
	insert_node(&(ats->root), data, compare_token);
	*i_copy = i_read;
	*nb_redir = 0;
	return (i_read);
}

int	copy_cmd_token(t_ats *ats, int *nb_redir, int i_read, int *i_copy)
{
	t_token		*data;

	data = init_node(&(ats->prompt[*i_copy]), i_read - *i_copy, *nb_redir,
			true);
	if (data != NULL)
	{
		insert_node(&(ats->root), data, compare_token);
		*i_copy = i_read;
	}
	if (ats->prompt[i_read] == '\0')
	{
		return (i_read);
	}
	i_read = place_cursor_after_token(ats->prompt, i_read);
	data = init_node(&(ats->prompt[*i_copy]), i_read - *i_copy, 0, false);
	if (data == NULL)
		return (FAILURE);
	insert_node(&(ats->root), data, compare_token);
	*i_copy = i_read;
	*nb_redir = 0;
	return (i_read);
}
