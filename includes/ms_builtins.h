/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:11:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 13:28:10 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTINS_H
# define MS_BUILTINS_H

# include <stdbool.h>
# include <errno.h>
# include <stdio.h>

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"

# define NB_BUILTINS 7

typedef struct s_builtin
{
	const char	*name;
	int			(*func)(char **args, t_list **envp, t_error *errors);
}	t_builtin;

int	is_builtins(const char *cmd);

int	exec_builtins(const char **tab_cmd, t_list **env, t_error *errors);

// BUILTINS

int	ms_echo(char **args, t_list **envp, t_error *errors);

int	ms_pwd(char **args, t_list **envp, t_error *errors);

int	ms_cd(char **args, t_list **envp, t_error *errors);

int	ms_unset(char **args, t_list **envp, t_error *errors);

int	ms_env(char **args, t_list **envp, t_error *errors);

int	ms_export(char **args, t_list **envp, t_error *errors);

int	ms_exit(char **args, t_list **envp, t_error *errors);

#endif