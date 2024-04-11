/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:07:05 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 16:15:19 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "redirection.h"

void	clean_child(t_maindata *core, char **args)
{
	if (args != NULL)
		ft_rm_split(args);
	clear_ats(core, CORE_ALL);
	exit (errno);
}

void	close_fds(t_maindata *core)
{
	if (core->history_fd != -1)
		close(core->history_fd);
	if (core->save_stdin != -1)
		close(core->save_stdin);
}

int	clean_parent(t_maindata *core_data, const t_ast *node)
{
	t_redir_data	*free_data_redir;
	t_kikidoc_data	*free_data_heredoc;

	if (node->data->index - 1 >= 0)
		close_pipe(core_data);
	while (node->data->nb_redir > 0)
	{
		free_data_redir = (t_redir_data *)ft_dequeue(core_data->q_redir);
		node->data->nb_redir--;
		if (free_data_redir->type_redir == REDIR_HEREDOC)
		{
			free_data_heredoc = ft_dequeue(core_data->q_kikidoc);
			free(free_data_heredoc->filename);
			free(free_data_heredoc->delimiter);
			free(free_data_heredoc);
		}
		free(free_data_redir->filename);
		free(free_data_redir);
	}
	return (SUCCESS);
}
