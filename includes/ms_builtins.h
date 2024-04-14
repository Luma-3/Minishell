/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:11:21 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 15:12:18 by jbrousse         ###   ########.fr       */
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

# define NB_BUILTINS 8

typedef struct s_builtin
{
	const char	*name;
	int			(*func)(char **args, t_list **envp, void *data);
}	t_builtin;

bool	is_builtin(const char *cmd);

int		chr_exec_bt(const char **tab_cmd, t_list **env, t_core *core_data);

// BUILTINS

int		ms_echo(char **args, t_list **envp, void *data);

int		ms_pwd(char **args, t_list **envp, void *data);

int		ms_cd(char **args, t_list **envp, void *data);

char	*spec_token(t_error *errors);

char	*oldpwd_token(t_list **env);

int		set_pwds(t_list **env, t_error *error);

int		ms_unset(char **args, t_list **envp, void *data);

int		ms_env(char **args, t_list **envp, void *data);

int		ms_export(char **args, t_list **envp, void *data);

bool	is_valid_name(char *name);

char	*get_name(char *arg);

char	*get_value(char *arg);

int		ms_exit(char **args, t_list **envp, void *data);

void	print_error_exit(char **args);

int		ms_history(char **args, t_list **envp, void *data);

#endif