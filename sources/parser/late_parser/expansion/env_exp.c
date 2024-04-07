/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:48:27 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 17:52:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

char	*copy_data_env(t_maindata *core_data, char *arg, int index)
{
	char	*new_arg;
	char	*token;
	char	*env_value;
	char	*tmp;
	int		i;

	i = index + 1;
	if (arg[i] == '?')
	{
		tmp = ft_itoa(core_data->last_status);
		new_arg = ft_insert_str(arg, tmp, "$?", index);
		free(tmp);
		if (new_arg == arg)
			return (arg);
		free(arg);
		return (new_arg);
	}
	while (arg[i] != '\0' && valid_env_char(arg[i]) == true && arg[i] != '$')
		i++;
	token = ft_substr(arg, index, i - index);
	if (token == NULL)
		return (arg);
	env_value = ms_getenv(core_data->env, token + 1);
	new_arg = ft_insert_str(arg, env_value, token, index);
	free(env_value);
	if (new_arg == arg)
		return (free(token), new_arg);
	free(arg);
	free(token);
	return (new_arg);
}

char	*handle_env(t_maindata *core_data, const char *arg)
{
	int		i;
	char	quote;
	char	*new_arg;

	i = 0;
	quote = '\0';
	new_arg = (char *)arg;
	while (new_arg[i])
	{
		if (new_arg[i] == '\"')
		{
			quote = check_quote(quote, new_arg[i]);
			i++;
		}
		if (new_arg[i] == '\'' && quote == '\0')
			i = skip_quote_parenthesis(new_arg, i);
		if (new_arg[i] == '$' && (ft_iswhitespace(new_arg[i + 1]) == false
				|| new_arg[i + 1] != '\0'))
		{
			new_arg = copy_data_env(core_data, new_arg, i);
		}
		if (new_arg[i] != '\0')
			i++;
	}
	return (new_arg);
}
