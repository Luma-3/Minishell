/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:39:53 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 16:22:31 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"
#include "core_data.h"

static void	_init_struct(t_error *errors, const char **msg_error)
{
	int		i;
	int		code;

	i = 0;
	code = 137;
	while (i < __NB_ERRORS_)
	{
		errors[i].code = code;
		errors[i].msg = (char *)msg_error[i];
		i++;
		code++;
	}
}

void	__init_error__(t_error *errors)
{
	const char	*msg_error[__NB_ERRORS_] = {EMSG_ENOCNF, EMSG_ENVHOM,
		EMSG_ENOENV, EMSG_ENOUSR, EMSG_EINVID, EMSG_ESYNTAX, EMSG_EEOF};

	_init_struct(errors, msg_error);
}

static void	ft_perror(t_error *errors, const char *str, const char *token)
{
	ft_putstr_fd((char *)str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ft_strerror(errors, errno), 2);
	if (errno >= ESYNTAX && token)
	{
		ft_putstr_fd((char *)token, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	if (errno == EEOF)
		ft_putstr_fd(")", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

char	*ft_strerror(t_error *errors, int code)
{
	int		i;

	i = 0;
	while (i <= 255 && errors[i].code != code)
		i++;
	return (errors[i].msg);
}

void	perror_switch(t_error *errors, const char *str, const char *token)
{
	if (errno < 137)
		perror(str);
	else
		ft_perror(errors, str, token);
}
