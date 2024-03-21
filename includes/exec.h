/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:39:08 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/21 11:23:18 by jbrousse         ###   ########.fr       */
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

int		dup_pipe(t_ats *ats, int index);

int		read_ats(t_ats *ats, t_bin_tree *root);

pid_t	exec_std(t_ats *ats, const t_bin_tree *node);

int		exec_command(char **tab_cmd, t_list **env);

int		exec_subshell(t_ats *ats, t_bin_tree *node);

//PATH HANDLING

char	*get_path(t_list *env, char *tab);

#endif // EXEC_H