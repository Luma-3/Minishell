/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:26:11 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 14:50:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

static int	open_redir_out(t_queue_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (FAILURE);
	}
	if (access(redir->file_name, F_OK | W_OK) != 0)
	{
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_in(t_queue_redir *redir)
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

static int	open_redir_append(t_queue_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (FAILURE);
	if (access(redir->file_name, F_OK | W_OK) != 0)
		return (FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	open_redir_heredoc(t_queue *queue_heredoc)
{
	t_queue_heredoc	*heredoc;
	int				fd;

	heredoc = (t_queue_heredoc *)ft_dequeue(queue_heredoc);
	if (access(heredoc->file_name, F_OK | R_OK) != 0)
		return (FAILURE);
	fd = open(heredoc->file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	open_redir(t_queue *redir, t_queue *heredoc, const t_bin_tree *root)
{
	t_queue_redir	*node;
	int				exit_code;
	int				index;

	index = root->data->nb_redir;
	exit_code = SUCCESS;
	while (index > 0 && exit_code == SUCCESS)
	{
		node = (t_queue_redir *)ft_dequeue(redir);
		if (!node)
		{
			return (FAILURE);
		}
		if (node->type_redir == REDIR_IN)
			exit_code = open_redir_in(node);
		else if (node->type_redir == REDIR_OUT)
			exit_code = open_redir_out(node);
		else if (node->type_redir == REDIR_OUT_APPEND)
			exit_code = open_redir_append(node);
		else if (node->type_redir == REDIR_HEREDOC)
			exit_code = open_redir_heredoc(heredoc);
		index--;
	}
	return (exit_code);
}
