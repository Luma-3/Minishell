/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 23:18:11 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
// TODO: remove unecessary includes

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"

# include "env.h"

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

//HISTORY
void		ft_add_history(char *input, t_list *env);
void		ft_create_history(t_list *env);

//PRINT_ERROR
void		print_error_message(void);
void		print_error_arg(char token);
void		print_error_display(void);

void		init_signal(void);

int			wexit_status(int status);

#endif