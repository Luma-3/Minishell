/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:52:44 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 22:55:41 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "libft.h"
# include "core_data.h"

# include <string.h>

# define ENOCNF 137

# define EMSG_ENOCNF "Command not found"

void	__init_error__(t_error *errors);

void	ft_perror(t_error *errors, char *str);

char	*ft_strerror(t_error *errors, int code);

void	print_error_why(t_ats *ats, t_list *env);


// CLEARTOOL

void	clear_ats(t_ats *ats, int flag);

#endif