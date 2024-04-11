/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 14:18:33 by jbrousse         ###   ########.fr       */
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

int				open_redir(t_maindata *core_data, const t_ast *node);

void			handle_pipeline_redir(t_maindata *core_data);

int				open_redir_out(t_redir_data *redir);

int				open_redir_in(t_redir_data *redir);

int				open_redir_append(t_redir_data *redir);

int				open_redir_heredoc(t_queue *queue_heredoc);

int				handle_kikidoc(const char *prompt, t_maindata *core);

t_kikidoc_data	*creat_kikidoc(int id, const char *prompt, int index,
					t_error *errors);

void			free_kikidoc(t_kikidoc_data *kikidoc);

#endif