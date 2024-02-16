/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/16 18:02:59 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **tab, char *path)
{
	pid_t	pid;
	char	**env;

	env = ft_split(getenv("PATH"), ':');
	pid = fork();
	if (pid == 0)
	{
		execve(path, tab, env);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}