/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 17:26:08 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include "libft.h"
# include <stdbool.h>

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
	t_list	**env;
	bool	input_redir;
	int		current_index;
	int		pos_after_token;
	int		nb_pipe;
	int		nb_cmd;
}			t_prompt;

typedef struct s_token
{
	char	*cmd;
	char	**argv;
	bool	post_parser;
	int		nb_redir;
}			t_token;

typedef struct s_bin_tree
{
	t_token				*data;
	struct s_bin_tree	*left;
	struct s_bin_tree	*right;
}						t_bin_tree;

typedef struct s_ats
{
	char		*prompt;
	t_bin_tree	*root;
	t_queue		*queue;
	t_queue		*queue_heredoc;
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
	char	*content;
}			t_queue_heredoc;

#endif