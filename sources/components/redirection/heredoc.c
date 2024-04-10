/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 14:37:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <readline/readline.h>
#include "parser.h"

extern volatile int	g_sigreceiver;

static bool	stop_heredoc(char *line, const char *delimiter, t_error *errors)
{
	if (line == NULL)
	{
		errno = EEOF;
		perror_switch(errors, "kikishell", delimiter);
		return (true);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0
		&& ft_strlen(line) != 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

static int	open_heredoc(const char *delimiter, int fd, t_error *errors)
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
		if (g_sigreceiver == SIGINT)
		{
			g_sigreceiver = 0;
			break ;
		}
		if (stop_heredoc(line, delimiter, errors) == true)
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
									int id, t_error *errors)
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
		return (FAILURE);
	}
	if (heredoc_queue == NULL)
	{
		free(heredoc->file_name);
		free(heredoc->delimiter);
		free(heredoc);
		return (close(fd), FAILURE);
	}
	ft_enqueue(heredoc_queue, heredoc);
	return (open_heredoc(delimiter, fd, errors));
}

char	*get_delimiter(const char *prompt, int index, t_error *errors)
{
	size_t		i;
	char		*delimiter;

	i = 0;
	index += 2;
	index = ft_skip_whitespaces(prompt, index);
	while (prompt[index + i] && ft_iswhitespace(prompt[index + i]) == false)
		i++;
	delimiter = ft_strndup(prompt + index, i);
	if (delimiter == NULL)
		return (NULL);
	if (delimiter[0] == '\0')
	{
		errno = ESYNTAX;
		perror_switch(errors, "kikishell", "newline");
		free(delimiter);
		return (NULL);
	}
	return (delimiter);
}

int	handle_heredoc(const char *prompt, t_maindata *core)
{
	int		i;
	int		id;
	char	*delimiter;

	i = 0;
	id = 0;
	delimiter = NULL;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		if (is_redir_type(prompt + i) == REDIR_HEREDOC)
		{
			delimiter = get_delimiter(prompt, i, core->errors);
			if (delimiter == NULL)
				return (FAILURE);
			if (create_enqueue_heredoc(core->queue_heredoc,
					delimiter, id, core->errors) == FAILURE)
			{
				printf("error\n");
				return (free(delimiter), FAILURE);
			}
			id++;
		}
		i++;
	}
	return (SUCCESS);
}
