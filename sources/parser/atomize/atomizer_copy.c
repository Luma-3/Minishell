/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomizer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:17:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 13:46:55 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static char	*copy_whitout_parenthesis(char *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(cmd, " \t\n\v\f\r");
	if (tmp == NULL)
		return (NULL);
	free(cmd);
	if (*tmp != '(')
		return (tmp);
	cmd = ft_strndup(tmp + 1, ft_strlen(tmp) - 2);
	if (cmd == NULL)
		return (NULL);
	free(tmp);
	return (cmd);
}

static t_token	*init_node(const char *cmd, int size_cmd)
{
	t_token	*data;

	data = (t_token *)malloc(sizeof(t_token));
	if (!data)
		return (NULL);
	data->is_subshell = false;
	data->post_parser = false;
	if (is_subshell(cmd, size_cmd) == true)
		data->is_subshell = true;
	else if (is_operator(cmd) == false)
		data->post_parser = true;
	data->cmd = copy_whitout_parenthesis((char *)cmd);
	if (data->cmd == NULL)
		return (free(data), NULL);
	data->argv = NULL;
	data->require_wait = true;
	data->post_parser = true;
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
		return (free(data), NULL);
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
	data->post_parser = false;
	if (insert_node(&(core->root), data, compare_token) == FAILURE)
		return (free(data), FAILURE);
	if (*(data->cmd) == '&')
		data->exit_code = EXIT_SUCCESS;
	else
		data->exit_code = EXIT_FAILURE;
	*i_copy = *i_read;
	return (SUCCESS);
}

t_token	*copy_token(t_maindata *core_data, const char *prompt, int size_copy)
{
	t_token	*token;
	char	*prompt_copy;
	int		nb_redir;
	bool	is_subshell;

	nb_redir = 0;
	prompt_copy = take_redir(core_data, prompt, size_copy, &nb_redir);
	if (prompt_copy == NULL)
		return (NULL);
	is_subshell = is_pipeline(prompt_copy);
	prompt_copy = handle_wildcard(core_data, prompt_copy);
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
