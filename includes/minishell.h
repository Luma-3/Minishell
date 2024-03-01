/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 16:51:43 by antgabri         ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
// TODO: remove unecessary includes

# include "convention.h"
# include "libft.h"
# include "core_data.h"

# include "env.h"

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

// DONE 
int			parser_init(t_prompt *prompt, char *input, t_list **env);

int			launch_child(t_prompt *prompt);

//HISTORY
void		ft_add_history(char *input, t_list *env);
void		ft_create_history(t_list *env);

//PRINT_ERROR
void		print_error_message(void);
void		print_error_arg(char token);
void		print_error_display(void);


#endif