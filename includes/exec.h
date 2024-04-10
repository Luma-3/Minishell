/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:39:08 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/11 00:06:27 by jbrousse         ###   ########.fr       */
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

int		dup_pipe(t_maindata *core_data, int index);

int		close_pipe(t_maindata *core_data);

// EXEC

int		pre_process_exec(t_maindata *core_data, t_ats *node);

int		read_ats(t_maindata *core_data, t_ats *root);

void	exec_std(t_maindata *core_data, const t_ats *node);

void	exec_command(char **tab_cmd, t_list **env, t_error *errors, char *path);

int		exec_subshell(t_maindata *core_data, t_ats *node);

int		clean_parent(t_maindata *core_data, const t_ats *node);

// PIPE_UTILS

void	close_all_pipes(t_maindata *core_data);

//BUILTINS

void	process_built_in(t_maindata *core_data, t_ats *node, char **args);

//PATH HANDLING

char	*get_path(char *path, char *tab);

#endif // EXEC_H