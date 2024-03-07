/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:00:24 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 17:54:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>
# include <readline/readline.h>
# include <stdbool.h>

# include "convention.h"
# include "libft.h"

int			test_exec_prog(char *tab);
int			test_path_access(char *tab);

void		create_enqueue_heredoc(t_queue *heredoc_queue, char *delimiter);

#endif