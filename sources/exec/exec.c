/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:00:16 by antgabri          #+#    #+#             */
/*   Updated: 2024/02/25 17:14:50 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_process(t_child *child, int i, int count_pipe)
{
	if (count_pipe > 0)
		close_pipe(child, i, count_pipe + 1);
	waitpid(child[i].pid, NULL, 0);
}

static int	launch_child(t_child *child,
	int count_pipe, char **tab, t_list *env)
{
	int	i;

	i = 0;
	while (i < nb_array(tab))
	{
		child[i].pid = fork();
		if (child[i].pid < 0)
			return (FAILURE);
		else if (child[i].pid == 0)
		{
			if (count_pipe > 0)
			{
				child = dup_in_out_child(child, i, count_pipe + 1);
				if (child == NULL)
					return (FAILURE);
			}
			if (exec_command(tab[i], env) == FAILURE)
				exit(FAILURE);
			exit(SUCCESS);
		}
		else
			handle_parent_process(child, i, count_pipe);
		i++;
	}
	return (SUCCESS);
}

static int	prepare_launch(char **tab, t_list *env,
	t_child *child, int count_pipe)
{
	int	count_arg;

	count_arg = nb_array(tab);
	child = connect_pipe(child, count_pipe); //CHANGER NOM P0UR CREATE_PIPE
	if (child == NULL)
		return (free_tab_exec(tab), free(child), FAILURE);
	if (launch_child(child, count_pipe, tab, env) == FAILURE)
		return (free_tab_exec(tab), free(child), FAILURE);
	else
		return (free_tab_exec(tab), free(child), SUCCESS);
}

int	exec(t_list *env, char *prompt)
{
	t_child	*child;
	char	**tab;
	char	**tab_temp;
	int		count_arg;
	int		count_pipe;

	child = NULL;
	prompt = ft_strtrim(prompt, " ");
	tab_temp = ft_split(prompt, '|');
	if (tab_temp == NULL)
		return (FAILURE);
	free(prompt);
	count_pipe = nb_array(tab_temp) - 1;
	tab = handle_token(tab_temp, 0);
	count_arg = nb_array(tab);
	child = init_child(child, count_arg);
	if (child == NULL)
		return (free_tab_exec(tab), FAILURE); //FREE TAB TEMP, FAILURE)
	if (tab != tab_temp)
		free_tab_exec(tab_temp);
	if (prepare_launch(tab, env, child, count_pipe) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
