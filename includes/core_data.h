/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 23:05:54 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include "libft.h"
# include <stdbool.h>

# define ATS_REDIR 0x01
# define ATS_HEREDOC 0x02
# define ATS_ENV 0x04
# define ATS_PROMPT 0x08
# define ATS_ROOT 0x10
# define ATS_PIPE 0x20

typedef struct s_child
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;
}			t_child;

typedef struct s_token
{
	int				index;
	int				nb_redir;
	int				exit_code;
	pid_t			pid;
	char			*cmd;
	char			**argv;
	bool			post_parser;
	bool			is_subshell;
	bool			require_wait;
}			t_token;

typedef struct s_bin_tree
{
	t_token				*data;
	struct s_bin_tree	*left;
	struct s_bin_tree	*right;
}						t_bin_tree;

typedef struct s_ats
{
	t_bin_tree	*root;
	t_list		*env;
	t_queue		*queue_heredoc;
	t_queue		*queue_redir;
	t_queue		*queue_pipe;
	int			last_status;
	char		*prompt;
}				t_ats;

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