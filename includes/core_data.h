/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/05 17:57:20 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include "libft.h"

# include <errno.h>
# include <sys/wait.h>
# include <stdbool.h>

# define CORE_REDIR		0x01
# define CORE_HEREDOC	0x02
# define CORE_ENV		0x04
# define CORE_PROMPT	0x08
# define CORE_ROOT		0x10
# define CORE_PIPE		0x20
# define CORE_UNAME		0x40
# define CORE_PATH		0x80
# define CORE_ALL		0xFF

# define FAILURE	-1
# define SUCCESS	0 

# define READ 0
# define WRITE 1

# define SIGINT 2

# define HELLO_MSG 	"toilet -tf future --gay -F border Welcome in KIKISHELL"
# define BYE_MSG 	"toilet -tf future --gay -F border See you soon !!!"
# define SAFE_MSG 	"toilet -tf future --gay -F border Welcome in SAFEKIKI"

# define PROMPT_SHELL	"\001\033[1;32m┗━━▶\002\033[0m "
# define PROMPT_SAFE	"> "

// ERRORS

typedef struct s_error
{
	int		code;
	char	*msg;
}			t_error;

// END ERRORS

typedef struct s_token
{
	int				index;
	int				nb_redir;
	int				exit_code;
	pid_t			pid;
	char			*cmd;
	bool			is_subshell;
	bool			require_wait;
}			t_token;

typedef struct s_tree_asterisk
{
	char		*data;
	t_queue		*branch;
}			t_tree_asterisk;

typedef struct s_ats
{
	t_token			*data;
	struct s_ats	*left;
	struct s_ats	*right;
}						t_ats;

typedef struct s_maindata
{
	t_ats		*root;
	t_list		*env;
	t_queue		*queue_heredoc;
	t_queue		*queue_redir;
	t_queue		*queue_pipe;
	int			last_status;
	char		*prompt;
	t_error		*errors;
	char		*path;
	char		*uname;
	int			history_fd;
	int			stdin_fd;
	bool		is_pipeline;
}				t_maindata;

// queue

typedef struct s_queue_redir
{
	int		type_redir;
	char	*file_name;
}			t_queue_redir;

typedef struct s_queue_heredoc
{
	char	*delimiter;
	char	*file_name;
}			t_queue_heredoc;

typedef struct s_queue_pipe
{
	int		pipe_fd[2];
	int		index;
}			t_queue_pipe;

#endif
