/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_wildcard_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:51:57 by anthony           #+#    #+#             */
/*   Updated: 2024/03/27 17:52:08 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "parser.h"

// char	*get_wildcard(char *prompt, int index)
// {
// 	char	*env_name;
// 	int		i;

// 	env_name = NULL;
// 	i = index;
// 	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
// 		&& prompt[i] != '$' && is_parenthesis(prompt[i]) == false
// 		&& is_quote(prompt[i]) == false)
// 		i++;
// 	if (i == index)
// 		return (NULL);
// 	env_name = ft_strndup(prompt + index, i - index);
// 	if (env_name == NULL)
// 		return (NULL);
// 	return (env_name);
// }





// static char	*delete_wildcard(char *prompt, char token, int index)
// {
// 	char	*new_prompt;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new_prompt = calloc(sizeof(char), ft_strlen(prompt) + 1);
// 	if (new_prompt == NULL)
// 		return (NULL);
// 	while (prompt[i] && i < index)
// 	{
// 		new_prompt[j++] = prompt[i++];
// 	}
// 	i++;
// 	while (ft_iswhitespace(prompt[i]) == false && prompt[i] != '\0'
// 		&& prompt[i] != token && is_parenthesis(prompt[i]) == false
// 		&& is_quote(prompt[i]) == false)
// 		i++;
// 	while (prompt[i])
// 	{
// 		new_prompt[j++] = prompt[i++];
// 	}
// 	free(prompt);
// 	return (new_prompt);
// }

// char	*copy_data_env(t_maindata *core_data, char *arg)
// {
// 	char	*to_replace;

// 	if (wild_data != NULL)
// 	{
// 		to_replace = ms_getenv(core_data->env, wild_data);
// 		if (to_replace == NULL)
// 			return (free(wild_data), delete_wildcard(prompt, '$', index));
// 		arg = put_wildcard(prompt, to_replace, '$', index);
// 		(free(wild_data), free(to_replace));
// 		return (prompt);
// 	}
// 	else
// 		return (delete_wildcard(prompt, '$', index));
// }

// char	*copy_data_tilde(t_maindata *core_data, char *prompt,
// 	char *wild_data, int index)
// {
// 	char	*to_replace;

// 	if (wild_data != NULL)
// 	{
// 		to_replace = ms_getenv(core_data->env, wild_data);
// 		if (to_replace == NULL)
// 			return (free(wild_data), delete_wildcard(prompt, '~', index));
// 		prompt = put_wildcard(prompt, to_replace, '~', index);
// 		(free(wild_data), free(to_replace));
// 		return (prompt);
// 	}
// 	else
// 		return (delete_wildcard(prompt, '~', index));
// }
