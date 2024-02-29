/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 15:25:25 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_DATA_H
# define CORE_DATA_H

# include "libft.h"

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

#endif