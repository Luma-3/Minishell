/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:39:31 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/26 14:26:35 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "display.h"

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
	int		fd;
	char	*path_atom[5];
	char	*path;

	path_atom[0] = "/home/";
	path_atom[1] = (char *)uname;
	path_atom[2] = "/";
	path_atom[3] = (char *)name;
	path_atom[4] = NULL;
	path = assemble(path_atom);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	printf("path = %s | fd = %d\n", path, fd);
	free(path);
	if (fd == -1)
		return (errno = EBADFD, FAILURE);
	return (fd);
}

int	get_history(int fd)
{
	char	*input;

	while (1)
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
