/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/26 13:16:39 by antgabri         ###   ########.fr       */
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

# include "env.h"

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

//HISTORY
int			ft_add_history(char *input, t_list *env);
int			ft_create_history(t_list *env);

//SIGNAL
void		init_signal(void);

#endif