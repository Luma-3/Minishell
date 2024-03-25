/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:52:44 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/25 11:11:59 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "libft.h"
# include "core_data.h"

# include <string.h>
# include <errno.h>
# include <stdio.h>

# define __NB_ERRORS_ 2

# define ENOCNF 137
# define ENVHOM 138
# define ENOENV 139

# define EMSG_ENOCNF "Command not found"
# define EMSG_ENVHOM "HOME not set"
# define EMSG_ENOENV "Environment not set"

void	__init_error__(t_error *errors);

void	ft_perror(t_error *errors, char *str);

char	*ft_strerror(t_error *errors, int code);

void	perror_switch(t_error *errors, char *str);

void	print_error_why(t_list *env);


// CLEARTOOL

void	clear_ats(t_ats *ats, int flag);

#endif