/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:51:57 by anthony           #+#    #+#             */
/*   Updated: 2024/03/27 14:14:14 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*get_wildcard(char *prompt, int index)
{
	char	*env_name;
	int		i;

	env_name = NULL;
	i = index;
	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
		&& prompt[i] != '$' && is_parenthesis(prompt[i]) == false
		&& is_quote(prompt[i]) == false)
		i++;
	if (i == index)
		return (NULL);
	env_name = ft_strndup(prompt + index, i - index);
	if (env_name == NULL)
		return (NULL);
	return (env_name);
}

char	*copy_wildcard(char *prompt, char *new_prompt,
	char	*data_wildcard, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt[i] && i <= index)
		new_prompt[j++] = prompt[i++];
	i = 0;
	while (data_wildcard[i])
		new_prompt[j++] = data_wildcard[i++];
	return (new_prompt);
}

char	*put_wildcard(char *prompt, char *data_wildcard, char token, int index)
{
	char	*new_prompt;
	char	*prompt_tmp;
	int		i;

	if (data_wildcard == NULL)
		return (prompt);
	while (prompt[index] != '\0' && prompt[index] != token)
		index++;
	if (prompt[index] == '\0')
		i = index;
	else
		i = index + 1;
	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
		&& prompt[i] != token && is_parenthesis(prompt[i]) == false
		&& is_quote(prompt[i]) == false)
		i++;
	prompt_tmp = calloc(sizeof(char), ft_strlen(prompt) - (i - index)
			+ ft_strlen(data_wildcard) + 1);
	if (prompt_tmp == NULL)
		return (NULL);
	prompt_tmp = copy_wildcard(prompt, prompt_tmp, data_wildcard, index - 1);
	new_prompt = ft_strjoin(prompt_tmp, prompt + i);
	free(prompt_tmp);
	free(prompt);
	return (new_prompt);
}

static char	*delete_wildcard(char *prompt, char token, int index)
{
	char	*new_prompt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_prompt = calloc(sizeof(char), ft_strlen(prompt) + 1);
	if (new_prompt == NULL)
		return (NULL);
	while (prompt[i] && i < index)
	{
		new_prompt[j++] = prompt[i++];
	}
	i++;
	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
		&& prompt[i] != token && is_parenthesis(prompt[i]) == false
		&& is_quote(prompt[i]) == false)
		i++;
	while (prompt[i])
	{
		new_prompt[j++] = prompt[i++];
	}
	free(prompt);
	return (new_prompt);
}

char	*copy_data_env(t_maindata *core_data, char *prompt,
	char *wild_data, int index)
{
	char	*to_replace;

	if (wild_data != NULL)
	{
		to_replace = ms_getenv(core_data->env, wild_data);
		if (to_replace == NULL)
			return (free(wild_data), delete_wildcard(prompt, '$', index));
		prompt = put_wildcard(prompt, to_replace, '$', index);
		(free(wild_data), free(to_replace));
		return (prompt);
	}
	else
		return (delete_wildcard(prompt, '$', index));
}

char	*copy_data_tilde(t_maindata *core_data, char *prompt,
	char *wild_data, int index)
{
	char	*to_replace;

	if (wild_data != NULL)
	{
		to_replace = ms_getenv(core_data->env, wild_data);
		if (to_replace == NULL)
			return (free(wild_data), delete_wildcard(prompt, '~', index));
		prompt = put_wildcard(prompt, to_replace, '~', index);
		(free(wild_data), free(to_replace));
		return (prompt);
	}
	else
		return (delete_wildcard(prompt, '~', index));
}
