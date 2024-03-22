/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:52:44 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 14:59:32 by jbrousse         ###   ########.fr       */
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

// CLEARTOOL

void	clear_ats(t_ats *ats, int flag);

#endif