/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:39:08 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 20:52:34 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>
# include <stdio.h>

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"
# include "environement.h"

// PIPE

int		dup_pipe(t_maindata *ats, int index);

int		close_pipe(t_maindata *ats);

int		handle_pipeline(t_maindata *ats, const t_ats *node);

// EXEC

int		read_ats(t_maindata *ats, t_ats *root);

pid_t	exec_std(t_maindata *ats, const t_ats *node);

int		exec_command(char **tab_cmd, t_list **env, t_error *errors);

int		exec_subshell(t_maindata *ats, t_ats *node);

int		clean_parent(t_maindata *ats, const t_ats *node);

//PATH HANDLING

char	*get_path(t_list *env, char *tab);

#endif // EXEC_H