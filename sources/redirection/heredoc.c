/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 13:32:09 by jbrousse         ###   ########.fr       */
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

static int	create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter)
{
	t_queue_heredoc	*heredoc;
	char			*heredoc_name;
	int				fd;

	heredoc = (t_queue_heredoc *)malloc(sizeof(t_queue_heredoc));
	heredoc_name = ft_strjoin(".heredoc_", delimiter);
	if (heredoc_name == NULL || heredoc == NULL)
	{
		errno = ENOMEM;
		return (free(heredoc), errno);
	}
	heredoc->file_name = heredoc_name;
	heredoc->delimiter = delimiter;
	fd = open(heredoc->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(heredoc->file_name);
		free(heredoc);
		perror("minishell: heredoc");
		return (errno);
	}
	ft_enqueue(heredoc_queue, heredoc);
	return (open_heredoc(delimiter, fd));
}

void	handle_heredoc(const char *prompt, t_ats *ats)
{
	int		i;
	int		j;
	char	*delimiteur;

	i = 0;
	j = 0;
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
			delimiteur = ft_strndup(prompt + i, j);
			create_enqueue_heredoc(ats->queue_heredoc, delimiteur);
		}
		i++;
	}
}
