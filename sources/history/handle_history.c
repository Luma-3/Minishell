/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:39:31 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/25 20:25:37 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_trim_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	str[i] = '\0';
}

int	ft_add_history(char *input, t_list *env, int fd)
{
	int		fd;

	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
	add_history(input);
	return (SUCCESS);
}

int	open_history(const char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
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
}
