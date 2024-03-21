/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 22:20:02 by jbrousse         ###   ########.fr       */
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
# include <errno.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
// TODO: remove unecessary includes

# include "convention.h"
# include "libft.h"
# include "core_data.h"

# include "env.h"

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

//HISTORY
void		ft_add_history(char *input, t_list *env);
void		ft_create_history(t_list *env);

//PRESENTATION_DISPLAY
char		*ft_create_prompt(t_list *env);
int			presentation_display(t_ats *ats, t_list **env);
int			diff_position(char *display_message);
char		*handle_position(t_list *env, char *display_message);

//PRINT_ERROR
void		print_error_message(void);
void		print_error_arg(char token);
void		print_error_display(void);

void		init_signal(void);

void		clear_ats(t_ats *ats, int flag);

int			wexit_status(int status);

#endif