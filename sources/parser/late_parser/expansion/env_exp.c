/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:48:27 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 12:15:26 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

char *copy_data_env(t_maindata *core_data, char *arg, int index)
{
	char	*new_arg;
	char	*token;
	char	*env_value;
	int	i;

	i = index + 1;
	if (arg[i] == '?')
	{
		new_arg = ft_insert_str(arg,
			ft_itoa(core_data->last_status), "$?", index);
		free(arg);
		return (new_arg);
	}
	while (arg[i] != '\0' && is_valid_char_name_env(arg[i]) == true && arg[i] != '$')
		i++;
	token = ft_substr(arg, index, i - index);
	if (token == NULL)
		return (arg);
	env_value = ms_getenv(core_data->env, token + 1);
	new_arg = ft_insert_str(arg, env_value, token, index);
	if (new_arg == arg)
		return (free(token), new_arg);
	free(arg);
	free(token);
	return (new_arg); 
}
