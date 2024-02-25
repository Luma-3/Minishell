/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/25 15:56:20 by anthony          ###   ########.fr       */
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

# include "libft.h"
# include "env.h"
# include <sys/wait.h>

# define FAILURE -1
# define SUCCESS 0

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

typedef struct s_child
{
	int		fd_pipe[2];
	pid_t	pid;
}	t_child;

int			count_words(const char *prompt);
int			count_letters(const char *prompt, int i);
int			place_cursor(const char *prompt, int i);
char		**alloc_tab(char *prompt);
int			isquote_type(char c);

//PARSING
char		*get_path(t_list *env, char *tab);
int			verif_arg(char *prompt);

//EXEC
int			exec(t_list *env, char *prompt);
int			exec_command(char *tab, t_list *env);

//PRINT_ERROR
void		print_error_message(void);
void		print_error_arg(char token);
void		print_error_display(void);

//EXEC_UTILS
int			nb_array(char **tab);
int			wait_child(t_child *child, int nb_child);

//HANDLE TOKEN
char		**ft_copy_tab(char **temp);
char		**handle_token(char **tab, int i);
int			verif_token(char *prompt, char token);
int			ft_search_token(char *tab, char *token);
int			is_there_token(char **tab, int i);

//HANDLE PIPE
t_child		*init_child(t_child *child, int nb_child);
t_child		*connect_pipe(t_child *child, int count_pipe);
t_child		*dup_in_out_child(t_child *child, int i, int count_pipe);
void		close_pipe(t_child *child, int i, int nb_pipe);

//
char		**ft_copy_tab_split(char **tab, int i, int pos_after_token);
int			ft_search_token(char *tab, char *token);
char		**place_new_split(char **tab, int i);

//ACCESS
int			test_exec_prog(char *tab);
int			test_path_access(char *tab);

//FREE
void		free_tab_exec(char **tab);
#endif