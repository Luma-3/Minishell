/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:11:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/28 15:58:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include <stdbool.h>
# include <errno.h>
# include <stdio.h>

# include "libft.h"
# include "convention.h"

# define NB_BUILTINS 7

typedef struct s_builtin
{
	const char	*name;
	int			(*func)(const char *prompt, char **args, t_list *envp);
}	t_builtin;

int	ms_echo(const char *prompt, char **args, t_list *envp);

int	ms_pwd(const char *prompt, char **args, t_list *envp);

int ms_cd(const char *prompt, char **args, t_list *envp);

int	ms_unset(const char *prompt, char **args, t_list *envp);

int	ms_env(const char *prompt, char **args, t_list *envp);

int	ms_export(const char *prompt, char **args, t_list *envp);

int	ms_exit(const char *prompt, char **args, t_list *envp);

#endif