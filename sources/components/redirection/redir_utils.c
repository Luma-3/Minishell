/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:16:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 14:27:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	open_redir_out(t_redir_data *redir)
{
	int	fd;

	if (access(redir->filename, F_OK) == 0
		&& access(redir->filename, W_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_in(t_redir_data *redir)
{
	int	fd;

	if (access(redir->filename, F_OK | R_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_append(t_redir_data *redir)
{
	int	fd;

	if (access(redir->filename, F_OK) == 0
		&& access(redir->filename, W_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_heredoc(t_queue *q_kikidoc)
{
	t_kikidoc_data	*kikidoc;
	int				fd;

	kikidoc = (t_kikidoc_data *)ft_dequeue(q_kikidoc);
	if (kikidoc == NULL)
		return (FAILURE);
	if (access(kikidoc->filename, F_OK) != 0)
		return (free_kikidoc(kikidoc), FAILURE);
	if (access(kikidoc->filename, R_OK) != 0)
	{
		unlink(kikidoc->filename);
		return (free_kikidoc(kikidoc), FAILURE);
	}
	fd = open(kikidoc->filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		unlink(kikidoc->filename);
		return (free_kikidoc(kikidoc), FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(kikidoc->filename);
	free_kikidoc(kikidoc);
	return (SUCCESS);
}
