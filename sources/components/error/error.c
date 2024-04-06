/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:39:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/06 15:02:12 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "core_data.h"

static void	_init_msg_error_(char **msg_error)
{
	msg_error[0] = EMSG_ENOCNF;
	msg_error[1] = EMSG_ENVHOM;
	msg_error[2] = EMSG_ENOENV;
	msg_error[3] = EMSG_ENOUSR;
	msg_error[4] = EMSG_EINVID;
}

static void	_init_struct(t_error *errors, char **msg_error)
{
	int		i;
	int		code;

	i = 0;
	code = 137;
	while (i < __NB_ERRORS_)
	{
		errors[i].code = code;
		errors[i].msg = msg_error[i];
		i++;
		code++;
	}
}

void	__init_error__(t_error *errors)
{
	char	*msg_error[__NB_ERRORS_];

	_init_msg_error_(msg_error);
	_init_struct(errors, msg_error);
}

void	ft_perror(t_error *errors, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(ft_strerror(errors, errno), 2);
}

char	*ft_strerror(t_error *errors, int code)
{
	int		i;

	i = 0;
	while (i <= 255 && errors[i].code != code)
		i++;
	return (errors[i].msg);
}
