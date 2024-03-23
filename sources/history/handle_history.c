/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:39:31 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/23 14:25:12 by jbrousse         ###   ########.fr       */
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

int	ft_add_history(char *input, t_list *env)
{
	int		fd;
	char	*home;
	char	*temp;

	temp = NULL;
	home = ms_getenv(env, "HOME");
	if (home == NULL)
		return (FAILURE);
	temp = ft_strjoin(home, "/.ms_history");
	free(home);
	if (temp == NULL)
		return (FAILURE);
	fd = open(temp, O_CREAT | O_APPEND | O_RDWR);
	if (fd == -1)
		return (FAILURE);
	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
	add_history(input);
	close(fd);
	free(temp);
	return (SUCCESS);
}

int	ft_create_history(t_list *env)
{
	int		fd;
	char	*home;
	char	*temp;
	char	*input;

	home = ms_getenv(env, "HOME");
	if (home == NULL)
		return (errno = ENVHOM, FAILURE);
	temp = ft_strjoin(home, "/.ms_history");
	free(home);
	if (temp == NULL)
		return (errno = ENOMEM, FAILURE);
	fd = open(temp, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (errno = EBADFD, FAILURE);
	while (1)
	{
		input = get_next_line(fd);
		if (input == NULL)
			break ;
		ft_trim_end(input);
		add_history(input);
		free(input);
	}
	close(fd);
	free(temp);
	return (SUCCESS);
}
