/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 12:36:22 by jbrousse         ###   ########.fr       */
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

# include "libft.h"
# include "env.h"
# include "ms_builtins.h"

# define FAILURE -1
# define SUCCESS 0

# define READ 0
# define WRITE 1

# define T_NONE 1
# define T_OR 2
# define T_AND 3
# define T_PIPE 4

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

typedef struct s_child
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;
}			t_child;

typedef struct s_prompt
{
	char	*prompt;
	char	**tab;
	t_list	*env;
	bool	input_redir;
	int		current_index;
	int		pos_after_token;
	int		nb_pipe;
	int		nb_cmd;
}			t_prompt;

//PARSING
int			count_words(const char *prompt);
int			count_letters(const char *prompt, int i);
int			place_cursor(const char *prompt, int i);
char		**alloc_tab(char *prompt);
int			isquote_type(char c);

//PARSER_INIT
int			parser_init(t_prompt *prompt, char *input, t_list *env);

//GET PATH
char		*get_path(t_list *env, char *tab);

//TEST PATH / ACCESS
int			test_exec_prog(char *tab);
int			test_path_access(char *tab);

//VERIF
int			verif_arg(char *prompt);

//EXEC
int			launch_child(t_prompt *prompt);
int			exec_command(char **tab_cmd, t_list *env);

//HANDLE TOKEN
int			detect_token(t_prompt *prompt);
int			verif_token(char *prompt, char token);

//HANDLE PIPE
t_child		*init_child(t_child *child, int nb_child);

//HANDLE CMD
int 		handle_pipe(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);
int			handle_cmd(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);

//HANDLE AND
int			skip_next_cmd(t_prompt *prompt);
int			handle_and(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);
int			handle_parent_process(t_child *childs, int index_child);

//HANDLE OR
int			skip_next_choice(t_prompt *prompt);
int			handle_or(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);
//EXEC_UTILS
int			nb_array(char **tab);
int			wait_child(t_child *child, int nb_child);

//FREE
void		free_tab_exec(char **tab);

//PRINT_ERROR
void		print_error_message(void);
void		print_error_arg(char token);
void		print_error_display(void);

// IO REDIRECTION
void	dup2_read(t_child *childs, int index_child);

#endif