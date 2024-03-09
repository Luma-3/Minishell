/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:39:08 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/09 19:32:40 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

# include "convention.h"
# include "libft.h"
# include "core_data.h"
# include "env.h"

/*--------------------------*/
/*          TOKEN           */
/*--------------------------*/

# define T_NONE 1
# define T_OR 2
# define T_AND 3
# define T_PIPE 4

# define STOP -2
# define CONTINUE -3

int		detect_token(t_prompt *prompt);
int		verif_token(char *prompt, char token);

//HANDLE PIPE
int 	handle_pipe(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);

void	dup2_read_pipe(t_child *childs, int index_child);

//HANDLE AND
int		skip_next_cmd(t_prompt *prompt);
int		handle_and(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);
int		handle_parent_process(t_child *childs, int index_child);

//HANDLE OR
int		skip_next_choice(t_prompt *prompt);
int		handle_or(t_prompt *prompt, t_child *childs, bool input_redir, int index_child);

/*--------------------------*/
/*        EXECUTION         */
/*--------------------------*/

// int		launch_child(t_prompt *prompt);




void 		close_pipe(t_child *childs, int index_child);

int			nb_array(char **tab);
int			wait_child(t_child *child, int nb_child);



//////////////////////////////////////////////////////////////////////////
////////////////////WARNING: NEW EXEC. KEEP OUT ! ////////////////////////
//////////////////////////////////////////////////////////////////////////

int		handle_token(t_ats *ats, t_bin_tree *node, pid_t *pid);

int		read_ats(t_ats *ats, t_bin_tree *root);

pid_t	exec_std(t_ats *ats, const t_bin_tree *node, pid_t *pid);

int		exec_command(char **tab_cmd, t_list **env);

int		exec_subshell(t_ats *ats, t_bin_tree *node, pid_t *pid);

//PATH HANDLING

char	*get_path(t_list *env, char *tab);

#endif // EXEC_H