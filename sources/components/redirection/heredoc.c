/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/08 13:01:15 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <readline/readline.h>
#include "parser.h"

extern volatile int	g_sigreciever;

static void	heredoc_error(const char *delimiter)
{
	ft_putstr_fd("kikishell: warning: here-document \
delimited by end-of-file (wanted '", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static bool	stop_heredoc(char *line, const char *delimiter)
{
	if (line == NULL)
	{
		heredoc_error(delimiter);
		return (true);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

static int	open_heredoc(const char *delimiter, int fd)
{
	char	*line;
	char	*heredoc_display;
	int		stdin_fd;

	heredoc_display = ft_strjoin(delimiter, " > ");
	if (heredoc_display == NULL)
		return (ENOMEM);
	stdin_fd = dup(STDIN_FILENO);
	while (true)
	{
		line = readline(heredoc_display);
		if (g_sigreciever == SIGINT)
		{
			g_sigreciever = 0;
			break ;
		}
		if (stop_heredoc(line, delimiter) == true)
			break ;
		ft_putendl_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(fd);
	return (free(heredoc_display), SUCCESS);
}

static int	create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter,
									int id)
{
	t_queue_heredoc	*heredoc;
	char			*heredoc_name;
	char			*heredoc_id;
	int				fd;

	heredoc = (t_queue_heredoc *)malloc(sizeof(t_queue_heredoc));
	if (heredoc == NULL)
		return (errno = ENOMEM, FAILURE);
	heredoc_id = ft_itoa(id);
	if (heredoc_id == NULL)
	{
		free(heredoc);
		return (errno = ENOMEM, FAILURE);
	}
	heredoc_name = ft_strjoin(".heredoc_", heredoc_id);
	free(heredoc_id);
	if (heredoc_name == NULL)
	{
		free(heredoc);
		return (errno = ENOMEM, FAILURE);
	}
	heredoc->file_name = heredoc_name;
	heredoc->delimiter = delimiter;
	fd = open(heredoc->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		perror("kikishell: heredoc");
		return (errno);
	}
	if (heredoc_queue == NULL)
	{
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		return (close(fd), FAILURE);
	}
	ft_enqueue(heredoc_queue, heredoc);
	return (open_heredoc(delimiter, fd));
}

void	handle_heredoc(const char *prompt, t_maindata *ats)
{
	int		i;
	int		j;
	int		id;
	char	*delimiteur;

	i = 0;
	j = 0;
	id = 0;
	delimiteur = NULL;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		if (is_redir_type(prompt + i) == REDIR_HEREDOC)
		{
			i += 2;
			i = ft_skip_whitespaces(prompt, i);
			while (prompt[i + j] && ft_iswhitespace(prompt[i + j]) == false)
				j++;
			delimiteur = ft_strndup(prompt + i, (size_t)j);
			if (create_enqueue_heredoc(ats->queue_heredoc,
					delimiteur, id) == FAILURE)
			{
				free(delimiteur);
				return ;
			}
			id++;
		}
		i++;
	}
}
