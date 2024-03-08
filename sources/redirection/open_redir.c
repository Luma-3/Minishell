/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/08 18:19:54 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

static int	open_redir_out(t_queue_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (errno);
	if (access(redir->file_name, F_OK | W_OK) == -1)
		return (errno);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_in(t_queue_redir *redir)
{
	int	fd;

	if (access(redir->file_name, F_OK | R_OK) == -1)
		return (errno);
	fd = open(redir->file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (errno);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_append(t_queue_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (errno);
	if (access(redir->file_name, F_OK | W_OK) == -1)
		return (errno);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_heredoc(t_queue *queue_heredoc)
{
	t_queue_heredoc	*heredoc;

	heredoc = (t_queue_heredoc *)ft_dequeue(queue_heredoc);
	ft_putstr_fd(heredoc->content, STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
	return (SUCCESS);
}

int	open_redir(t_ats *ats, const t_bin_tree *node)
{
	t_queue_redir	*redir;
	int				exit_code;

	exit_code = SUCCESS;
	while (node->data->nb_redir > 0 && exit_code == SUCCESS)
	{
		redir = (t_queue_redir *)ft_dequeue(ats->queue);
		if (redir->type_redir == REDIR_IN)
			exit_code = open_redir_in(redir);
		else if (redir->type_redir == REDIR_OUT)
		{
			exit_code = open_redir_out(redir);
		}
		else if (redir->type_redir == REDIR_OUT_APPEND)
		{
			exit_code = open_redir_append(redir);
		}
		else if (redir->type_redir == REDIR_HEREDOC)
		{
			exit_code = open_redir_heredoc(ats->queue_heredoc);
		}
		node->data->nb_redir--;
	}
	return (exit_code);
}
