/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats_copy_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:17:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 19:53:40 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static char	*copy_whitout_parenthesis(char *cmd)
{
	char	*tmp;
	int		i;

	if (cmd == NULL)
		return (NULL);
	i = ft_skip_whitespaces(cmd, 0);
	if (cmd[i] != '(')
		return (cmd);
	tmp = ft_strtrim(cmd, " \t\n\v\f\r");
	free(cmd);
	cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
	free(tmp);
	return (cmd);
}

static t_token	*init_node(const char *cmd, int size_cmd)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->is_subshell = false;
	token->post_parser = false;
	if (is_subshell(cmd, size_cmd) == true)
		token->is_subshell = true;
	else if (is_operator(cmd) == false)
		token->post_parser = true;
	token->cmd = copy_whitout_parenthesis((char *)cmd);
	token->argv = NULL;
	token->last_cmd = false;
	return (token);
}

int	copy_cmd_operator(t_ats *ats, int *i_copy, int *i_read)
{
	t_token	*data;

	data = copy_token(ats, ats->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	data->post_parser = true;
	insert_node(&(ats->root), data, compare_token);
	*i_copy = *i_read;
	*i_read += 2;
	data = copy_token(ats, ats->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	data->post_parser = false;
	insert_node(&(ats->root), data, compare_token);
	*i_copy = *i_read;
	return (SUCCESS);
}

t_token	*copy_token(t_ats *ats, const char *prompt, int size_copy)
{
	t_token	*token;
	char	*prompt_copy;
	int		nb_redir;
	bool	is_subshell;

	nb_redir = 0;
	prompt_copy = take_redir(ats, prompt, size_copy, &nb_redir);
	if (prompt_copy == NULL)
		return (NULL);
	is_subshell = is_pipeline(prompt_copy);
	token = init_node(prompt_copy, size_copy);
	if (token == NULL)
		return (NULL);
	if (token->is_subshell == false)
	{
		token->is_subshell = is_subshell;
	}
	token->nb_redir = nb_redir;
	return (token);
}
