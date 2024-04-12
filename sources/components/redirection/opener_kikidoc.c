/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener_kikidoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 16:39:29 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <readline/readline.h>
#include "parser.h"
#include "minishell.h"

extern volatile int	g_sigreceiver;

void	free_kikidoc(t_kikidoc_data *kikidoc)
{
	if (kikidoc == NULL)
		return ;
	if (kikidoc->filename != NULL)
		free(kikidoc->filename);
	if (kikidoc->delimiter != NULL)
		free(kikidoc->delimiter);
	free(kikidoc);
}

static bool	stop_heredoc(char *line, const char *delimiter, t_error *errors)
{
	if (line == NULL)
	{
		errno = EEOF;
		perror_switch(errors, "kikishell: kikidoc", delimiter);
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
			free(heredoc_display);
			restore_stdin(errors, stdin_fd);
			return (close(fd), FAILURE);
		}
		if (stop_heredoc(line, delimiter, errors) == true)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	restore_stdin(errors, stdin_fd);
	return (free(heredoc_display), close(fd), SUCCESS);
}

static int	enqueue_kikidoc(t_queue *kikidoc_queue, t_kikidoc_data *kikidoc,
	t_error *errors)
{
	int				fd;

	fd = open(kikidoc->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free_kikidoc(kikidoc);
		perror_switch(errors, "kikishell: kikidoc", NULL);
		return (FAILURE);
	}
	if (kikidoc_queue == NULL)
	{
		free_kikidoc(kikidoc);
		return (close(fd), FAILURE);
	}
	ft_enqueue(kikidoc_queue, kikidoc);
	return (open_heredoc(kikidoc->delimiter, fd, errors));
}

int	handle_kikidoc(const char *prompt, t_maindata *core)
{
	int				i;
	int				id;
	t_kikidoc_data	*kikidoc;

	i = 0;
	id = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		if (is_redir_type(prompt + i) == REDIR_HEREDOC)
		{
			kikidoc = creat_kikidoc(id, prompt, i, core->errors);
			if (kikidoc == NULL)
				return (FAILURE);
			if (enqueue_kikidoc(core->q_kikidoc, kikidoc, core->errors)
				== FAILURE)
			{
				return (FAILURE);
			}
			id++;
		}
		i++;
	}
	return (SUCCESS);
}
