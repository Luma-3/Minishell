/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 17:20:18 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
// TODO: remove unecessary includes

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"

# include "environement.h"

# define ERROR_FORMAT "Minishell error"

//SIGNAL
void		init_signal(void);

void		exec_process(t_maindata *ats, t_list *env, char *input);

int			init_shell(t_maindata *core_data, t_error *errors, char **envp);

int			init_safe_mode(t_maindata *core_data);

//HISTORY

int			get_history(int fd);

int			open_history(const char *name, const char *uname);

int			ft_add_history(char *input, int fd);

char		*get_home(const char *uname);

#endif