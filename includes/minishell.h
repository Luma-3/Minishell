/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:23:23 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 17:23:07 by antgabri         ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define FAILURE -1
# define SUCCESS 0

# define ERROR_FORMAT "Minishell error"
//int	g_sig_return;

int		count_words(const char *prompt);
int		count_letters(const char *prompt, int i);
int		place_cursor(const char *prompt, int i);
char	**alloc_tab(char *prompt);
int		isquote_type(char c);

char	*get_path(char **tab);
void	print_error_message(void);
#endif