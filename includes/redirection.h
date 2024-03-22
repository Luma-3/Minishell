/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 15:26:59 by jbrousse         ###   ########.fr       */
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
int		open_redir(t_queue *redir, t_queue *heredoc, const t_bin_tree *node);

int		open_all_redir(t_queue *redir, t_queue *heredoc, t_bin_tree *root);

#endif