/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:39:31 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/10 14:42:11 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "display.h"
#include "fcntl.h"

static void	ft_trim_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	str[i] = '\0';
}

int	ft_add_history(char *input, int fd)
{
	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
	add_history(input);
	return (SUCCESS);
}

int	open_history(const char *name, const char *uname)
{
	int			fd;
	const char	*path_atom[5] = {
		"/home/",
		(char *)uname,
		"/",
		(char *)name,
		NULL};
	char		*path;

	path = assemble(path_atom);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	free(path);
	if (fd == -1)
		return (errno = EBADFD, FAILURE);
	return (fd);
}

int	get_history(int fd)
{
	char	*input;

	while (true)
	{
		input = get_next_line(fd);
		if (input == NULL)
			break ;
		ft_trim_end(input);
		add_history(input);
		free(input);
	}
	return (SUCCESS);
}

void	verif_add_history(char *input, int fd)
{
	size_t	nb_space;

	nb_space = ft_skip_whitespaces(input, 0);
	if (nb_space != ft_strlen(input))
		ft_add_history(input, fd);
}
