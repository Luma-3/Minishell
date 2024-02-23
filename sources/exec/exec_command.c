/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:06:49 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/23 14:59:08 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(char *tab, t_list *env)
{
	char	*path_command;
	char	**env_tab;
	char	**command;

	path_command = get_path(env, tab);
	if (path_command == NULL)
		return (FAILURE);
	command = ft_split(tab, ' ');
	if (command == NULL)
		return (free(path_command), FAILURE);
	env_tab = env_to_tab(env);
	if (execve(path_command, command, env_tab) == -1)
		return (free(path_command), free(command), FAILURE);
	return (SUCCESS);
}
