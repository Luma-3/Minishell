/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:51:57 by anthony           #+#    #+#             */
/*   Updated: 2024/03/26 15:22:48 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static char	*get_env_name(char *prompt, int index)
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

static char	*copy_env_in_prompt(char *prompt, char *new_prompt,
	char *value_env, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt[i] && i < index)
		new_prompt[j++] = prompt[i++];
	i = 0;
	while (value_env[i])
		new_prompt[j++] = value_env[i++];
	return (new_prompt);
}

static char	*env_to_str(char *prompt, char *value_env, int index)
{
	char	*new_prompt;
	char	*prompt_tmp;
	int		i;

	while (prompt[index] != '\0' && prompt[index] != '$')
		index++;
	i = index + 1;
	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
		&& prompt[i] != '$' && is_parenthesis(prompt[i]) == false
		&& is_quote(prompt[i]) == false)
		i++;
	prompt_tmp = calloc(sizeof(char), ft_strlen(prompt) - (i - index)
			+ ft_strlen(value_env) + 1);
	if (prompt_tmp == NULL)
		return (NULL);
	prompt_tmp = copy_env_in_prompt(prompt, prompt_tmp, value_env, index);
	new_prompt = ft_strjoin(prompt_tmp, prompt + i);
	free(prompt_tmp);
	free(prompt);
	return (new_prompt);
}

static char	*delete_env_in_prompt(char *prompt, int index)
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
		&& prompt[i] != '$' && is_parenthesis(prompt[i]) == false
		&& is_quote(prompt[i]) == false)
		i++;
	while (prompt[i])
	{
		new_prompt[j++] = prompt[i++];
	}
	free(prompt);
	return (new_prompt);
}

char	*handle_env_prompt(t_maindata *core_data, char *prompt)
{
	int		i;
	char	*name_env;
	char	*value_env;

	i = 0;
	name_env = NULL;
	while (prompt[i])
	{
		if (prompt[i] == '$')
		{
			name_env = get_env_name(prompt, i + 1);
			if (name_env != NULL)
			{
				value_env = ms_getenv(core_data->env, name_env);
				if (value_env == NULL)
					return (free(name_env), delete_env_in_prompt(prompt, i));
				prompt = env_to_str(prompt, value_env, i);
				(free(name_env), free(value_env));
			}
			else
				prompt = delete_env_in_prompt(prompt, i);
		}
		i++;
	}
	return (prompt);
}
