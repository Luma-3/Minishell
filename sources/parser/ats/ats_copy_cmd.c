/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats_copy_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:17:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 19:35:39 by anthony          ###   ########.fr       */
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

t_token	*copy_insert_node(t_ats *ats, int i_copy, int i_read)
{
	t_token	*data;

	data = copy_token(ats, ats->prompt + i_copy, i_read - i_copy);
	if (data == NULL)
		return (NULL);
	if (insert_node(&(ats->root), data, compare_token) == FAILURE)
		return (free(data), NULL);
	return (data);
}

int	copy_cmd_operator(t_ats *ats, int *i_copy, int *i_read)
{
	t_token	*data;

	data = copy_token(ats, ats->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	if (insert_node(&(ats->root), data, compare_token) == FAILURE)
		return (free(data), FAILURE);
	*i_copy = *i_read;
	*i_read += 2;
	data = copy_token(ats, ats->prompt + *i_copy, *i_read - *i_copy);
	if (data == NULL)
		return (FAILURE);
	data->post_parser = false;
	if (insert_node(&(ats->root), data, compare_token) == FAILURE)
		return (free(data), FAILURE);
	if (*(data->cmd) == '&')
		data->exit_code = EXIT_SUCCESS;
	else
		data->exit_code = EXIT_FAILURE;
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
	printf("prompt: %s\n", prompt);
	prompt_copy = take_redir(ats, prompt, size_copy, &nb_redir);
	if (prompt_copy == NULL)
		return (NULL);
	is_subshell = is_pipeline(prompt_copy);
	printf("prompt_copy avant: %s\n", prompt_copy);
	prompt_copy = handle_env_prompt(ats, prompt_copy);
	printf("prompt_copy: %s\n", prompt_copy);
	token = init_node(prompt_copy, size_copy);//TODO handle NULL
	if (token == NULL)
		return (NULL);
	if (token->is_subshell == false)
	{
		token->is_subshell = is_subshell;
	}
	token->nb_redir = nb_redir;
	return (token);
}
