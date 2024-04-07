/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:16:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/07 16:49:16 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	open_redir_out(t_queue_redir *redir)
{
	int	fd;

	if (access(redir->file_name, F_OK) == 0
		&& access(redir->file_name, W_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_in(t_queue_redir *redir)
{
	int	fd;

	if (access(redir->file_name, F_OK | R_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_append(t_queue_redir *redir)
{
	int	fd;

	if (access(redir->file_name, F_OK) == 0
		&& access(redir->file_name, W_OK) != 0)
	{
		return (FAILURE);
	}
	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir_heredoc(t_queue *queue_heredoc)
{
	t_queue_heredoc	*heredoc;
	int				fd;

	heredoc = (t_queue_heredoc *)ft_dequeue(queue_heredoc);
	if (heredoc == NULL)
		return (FAILURE);
	if (access(heredoc->file_name, F_OK) != 0)
	{
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		return (FAILURE);
	}
	if (access(heredoc->file_name, R_OK) != 0)
	{
		unlink(heredoc->file_name);
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		return (FAILURE);
	}
	fd = open(heredoc->file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		unlink(heredoc->file_name);
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(heredoc->file_name);
	return (SUCCESS);
}
