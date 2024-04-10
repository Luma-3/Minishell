/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:52:44 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 13:07:42 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "libft.h"
# include "core_data.h"

# include <string.h>
# include <errno.h>
# include <stdio.h>

# define __NB_ERRORS_ 7

# define ENOCNF 	137
# define ENVHOM 	138
# define ENOENV 	139
# define ENOUSR 	140
# define EINVID 	141
# define ESYNTAX	142
# define EEOF		143

# define EMSG_ENOCNF	"Command not found"
# define EMSG_ENVHOM	"HOME not set"
# define EMSG_ENOENV	"Environment not set"
# define EMSG_ENOUSR	"User not found"
# define EMSG_EINVID	"not a valid identifier"
# define EMSG_ESYNTAX	"syntax error: near unexpected token '"
# define EMSG_EEOF		"warning: kiki-doc delimited by end-of-file (wanted '"

void	__init_error__(t_error *errors);

char	*ft_strerror(t_error *errors, int code);

void	perror_switch(t_error *errors, const char *str, const char *token);

void	print_error_why(void);

// CLEARTOOL

void	clear_ats(t_maindata *ats, int flag);

void	free_data_tree(void *content);

#endif