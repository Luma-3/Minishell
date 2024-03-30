/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 15:24:46 by anthony          ###   ########.fr       */
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
int		open_redir(t_queue *redir, t_queue *heredoc, const t_ats *node);

int		open_redirs_pipe(t_queue *redir, t_queue *heredoc, t_ats *root);

#endif