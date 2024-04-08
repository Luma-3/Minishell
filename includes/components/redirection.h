/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/08 14:59:51 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"

# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>

// int			create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter);
int		open_redir(t_maindata *core_data, const t_ats *node);

void	handle_pipeline_redir(t_maindata *core_data);

int		open_redir_out(t_queue_redir *redir);

int		open_redir_in(t_queue_redir *redir);

int		open_redir_append(t_queue_redir *redir);

int		open_redir_heredoc(t_queue *queue_heredoc);

#endif