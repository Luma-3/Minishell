/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:29:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"

# include "environement.h"

void		exec_process(t_core *ats, char *input);

int			init_shell(t_core *core_data, t_error *errors, char **envp);

int			init_safe_mode(t_core *core_data);

//HISTORY

int			get_history(int fd);

int			open_history(const char *name, const char *uname);

void		verif_add_history(char *input, int fd);

char		*get_home(const char *uname);

char		*get_uname(void);

//UTILS

void		restore_stdin(t_error *errors, int save_fd);

#endif