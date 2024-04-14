/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:39:08 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:18:31 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"
# include "environement.h"

// PIPE

int		dup_pipe(t_core *core_data, int index);

int		close_pipe(t_core *core_data);

// EXEC

int		pre_process_exec(t_core *core_data, t_ast *node);

int		read_ats(t_core *core_data, t_ast *root);

int		exec_std(t_core *core_data, const t_ast *node);

void	exec_command(char **tab_cmd, t_list **env, t_error *errors, char *path);

int		exec_subshell(t_core *core_data, t_ast *node);

int		clean_parent(t_core *core_data, const t_ast *node, char **args);

// PIPE_UTILS

void	close_all_pipes(t_core *core_data);

//BUILTINS

int		process_built_in(t_core *core_data, t_ast *node, char **args);

//PATH HANDLING

char	*get_path(char *path, char *tab);

void	clean_child(t_core *core, char **args);

void	close_fds(t_core *core);

#endif // EXEC_H