/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:04:47 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/06 14:37:19 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "parser.h"

static char	*create_heredoc(char *heredoc_content, const char *line)
{
	char *line_n;
	char *tmp;
	
	line_n = ft_strjoin(line, "\n");
	if (heredoc_content == NULL)
	{
		heredoc_content = ft_strdup(line_n);
	}
	else
	{
		tmp = ft_strjoin(heredoc_content, line_n);
		free(heredoc_content);
		heredoc_content = tmp;
	}
	free(line_n);
	return (heredoc_content);
}

static void	heredoc_error(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

char	*open_heredoc(const char *delimiter)
{
	char	*line;
	char 	*heredoc_name;
	char 	*heredoc_content;

	heredoc_name = ft_strjoin(delimiter, " > ");
	heredoc_content = NULL;
	while (true)
	{
		line = readline(heredoc_name);
		if (line == NULL)
		{
			heredoc_error(delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		heredoc_content = create_heredoc(heredoc_content, line);
	}
	free(heredoc_name);
	return (heredoc_content);
}

void create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter)
{
	char			*heredoc_content;
	t_queue_heredoc	*heredoc;

	heredoc_content = open_heredoc(delimiter);
	heredoc = (t_queue_heredoc *)malloc(sizeof(t_queue_heredoc));
	if (heredoc == NULL)
		return ;
	heredoc->delimiter = ft_strdup(delimiter);
	heredoc->content = heredoc_content;
	ft_enqueue(heredoc_queue, heredoc);
}