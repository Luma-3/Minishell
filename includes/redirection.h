/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 13:01:38 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>

# include "convention.h"
# include "core_data.h"
# include "libft.h"
# include <fcntl.h>
# include <errno.h>

int			test_exec_prog(char *tab);
int			test_path_access(char *tab);

// int			create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter);
int			open_redir(t_queue *redir, t_queue *heredoc, const t_bin_tree *node);

#endif