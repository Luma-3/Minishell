/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:18:32 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include "libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <stdbool.h>

// if you want print new line before and after the prompt : set to '\n'
// if don't want print new line before and after the prompt : set to '\0'
// initial value is '\n'
# define NEW_LINE_PRINT	'\n'

# define CORE_REDIR		0x01
# define CORE_HEREDOC	0x02
# define CORE_ENV		0x04
# define CORE_PROMPT	0x08
# define CORE_ROOT		0x10
# define CORE_PIPE		0x20
# define CORE_UNAME		0x40
# define CORE_PATH		0x80
# define CORE_HISTORY	0x100
# define CORE_STDIN		0x200
# define CORE_ALL		0x3FF

# define FAILURE	-1
# define SUCCESS	0 

# define READ 0
# define WRITE 1

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_OUT_APPEND 3
# define REDIR_HEREDOC 4

# define SIGINT 2
# define SIGQUIT 3

# define HELLO_MSG 	"toilet -tf future --gay -F border Welcome in KIKISHELL"
# define BYE_MSG 	"toilet -tf future --gay -F border See you soon !!!"
# define SAFE_MSG 	"toilet -tf future --gay -F border Welcome in SAFEKIKI"

# define PROMPT_SHELL	"\001\033[1;32m┗━━▶\002\033[0m "
# define HISTORY_FILE	".kiki_history"

// ERRORS

typedef struct s_error
{
	int		code;
	char	*msg;
}			t_error;

// END ERRORS

typedef struct s_token
{
	pid_t			pid;
	int				index;
	int				nb_redir;
	int				exit_code;
	char			*cmd;
	bool			is_subshell;
	bool			require_wait;
}			t_token;

typedef struct s_tree_asterisk
{
	t_queue		*branch;
	char		*data;
}			t_tree_asterisk;

typedef struct s_ast
{
	t_token			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}						t_ast;

typedef struct s_core
{
	t_ast		*root;
	t_list		*env;
	t_error		*errors;
	t_queue		*q_kikidoc;
	t_queue		*q_redir;
	t_queue		*q_pipe;
	int			save_stdin;
	int			history_fd;
	int			last_status;
	char		*prompt;
	char		*uname;
	char		*path;
	bool		is_pipeline;
}				t_core;

// queue

typedef struct s_redir_data
{
	int		type_redir;
	char	*filename;
}			t_redir_data;

typedef struct s_kikidoc_data
{
	char	*delimiter;
	char	*filename;
}			t_kikidoc_data;

typedef struct s_pipe_data
{
	int		pipe_fd[2];
	int		index;
}			t_pipe_data;

#endif
