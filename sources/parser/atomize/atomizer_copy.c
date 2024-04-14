/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomizer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:17:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 14:55:22 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
// #include "minishell.h"

static char	*copy_whitout_parenthesis(char *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(cmd, " \t\n\v\f\r");
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] == '(' && tmp[ft_strlen(tmp) - 1] == ')')
	{
		if (*tmp != '(')
			return (tmp);
		cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
		free(tmp);
		if (cmd == NULL)
			return (NULL);
		return (cmd);
	}
	return (tmp);
}

static t_token	*init_node(const char *cmd)
{
	t_token	*data;

	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
		return (NULL);
	data->is_subshell = false;
	if (is_subshell(cmd) == true)
		data->is_subshell = true;
	data->cmd = copy_whitout_parenthesis((char *)cmd);
	free((char *)cmd);
	if (data->cmd == NULL)
		return (free_data_tree(data), NULL);
	data->require_wait = true;
	data->exit_code = 0;
	data->pid = -1;
	data->index = -1;
	return (data);
}

t_token	*copy_insert_node(t_maindata *core_data, int i_copy, int i_read)
{
	t_token	*data;

	data = copy_token(core_data, core_data->prompt + i_copy, i_read - i_copy);
	if (data == NULL)
		return (NULL);
	if (insert_node(&(core_data->root), data, compare_token) == FAILURE)
		return (free_data_tree(data), NULL);
	return (data);
}

int	copy_cmd_operator(t_maindata *core, int *i_copy, int *i_read)
{
	t_token	*data;

	data = copy_token(core, core->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	if (insert_node(&(core->root), data, compare_token) == FAILURE)
		return (free(data), FAILURE);
	*i_copy = *i_read;
	*i_read += 2;
	data = copy_token(core, core->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	if (insert_node(&(core->root), data, compare_token) == FAILURE)
		return (free(data), FAILURE);
	if (*(data->cmd) == '&')
		data->exit_code = EXIT_SUCCESS;
	else
		data->exit_code = EXIT_FAILURE;
	*i_copy = *i_read;
	return (SUCCESS);
}

t_token	*copy_token(t_maindata *core, const char *prompt, size_t len_copy)
{
	t_token	*token;
	char	*prompt_copy;
	char	*prompt_no_redir;
	int		nb_redir;
	bool	subshell;

	nb_redir = 0;
	prompt_copy = ft_strndup(prompt, len_copy);
	if (prompt_copy == NULL)
		return (NULL);
	prompt_no_redir = take_redir(core, prompt_copy, &nb_redir);
	free(prompt_copy);
	if (prompt_no_redir == NULL)
		return (NULL);
	subshell = is_pipeline(prompt_no_redir);
	token = init_node(prompt_no_redir);
	if (token == NULL)
		return (NULL);
	if (token->is_subshell == false)
	{
		token->is_subshell = subshell;
	}
	token->nb_redir = nb_redir;
	return (token);
}
