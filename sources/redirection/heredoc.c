/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/09 23:19:58 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "parser.h"

static void	heredoc_error(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document \
		delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static bool	stop_heredoc(char *line, const char *delimiter)
{
	if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
	{
		free(line);
		return (true);
	}
	if (line == NULL)
	{
		heredoc_error(delimiter);
		return (true);
	}
	return (false);
}

static int	open_heredoc(const char *delimiter, int fd)
{
	char	*line;
	char	*heredoc_display;

	heredoc_display = ft_strjoin(delimiter, " > ");
	if (heredoc_display == NULL)
		return (ENOMEM);
	while (true)
	{
		line = readline(heredoc_display);
		if (stop_heredoc(line, delimiter) == true)
			break ;
		ft_putendl_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (free(heredoc_display), SUCCESS);
}

int	create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter)
{
	t_queue_heredoc	*heredoc;
	char			*heredoc_name;

	heredoc = (t_queue_heredoc *)malloc(sizeof(t_queue_heredoc));
	heredoc_name = ft_strjoin(".heredoc_", delimiter);
	if (heredoc_name == NULL || heredoc == NULL)
	{
		errno = ENOMEM;
		return (free(heredoc), errno);
	}
	heredoc->file_name = heredoc_name;
	heredoc->delimiter = delimiter;
	heredoc->fd = open(heredoc->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (heredoc->fd == -1)
	{
		free(heredoc->file_name);
		free(heredoc);
		perror("minishell: heredoc");
		return (errno);
	}
	ft_enqueue(heredoc_queue, heredoc);
	return (open_heredoc(delimiter, heredoc->fd));
}
