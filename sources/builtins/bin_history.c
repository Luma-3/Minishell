/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:19:54 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 16:20:14 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "display.h"
#include "ms_error.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>

static int	have_flag(char **arg)
{
	int	i;
	int	j;

	i = 1;
	if (arg[1] == NULL)
		return (1);
	while (arg[i])
	{
		if (arg[i][0] != '-')
			return (FAILURE);
		j = 1;
		while (arg[i][j] != '\0' && arg[i][0] == '-')
		{
			if (arg[i][j] == 'c')
				j++;
			else
				return (FAILURE);
		}
		if (j == 1)
			return (FAILURE);
		i++;
	}
	return (i);
}

static int	ft_clear_history(const char *path, t_core *core)
{
	rl_clear_history();
	if (unlink(path) == FAILURE)
	{
		perror_switch(core->errors, "kiki_history", NULL);
		return (errno);
	}
	close(core->history_fd);
	core->history_fd = open_history(HISTORY_FILE, core->uname);
	return (SUCCESS);
}

static char	*get_path_hist(char *uname, t_error *errors)
{
	char	*home;
	char	*path;
	char	*join_path[4];

	home = get_home(uname);
	if (home == NULL)
	{
		perror_switch(errors, "kiki_history", NULL);
		return (NULL);
	}
	join_path[0] = home;
	join_path[1] = "/";
	join_path[2] = HISTORY_FILE;
	join_path[3] = NULL;
	path = assemble((const char **)join_path);
	free(home);
	if (path == NULL)
	{
		perror_switch(errors, "kiki_history", NULL);
		return (NULL);
	}
	return (path);
}

static int	print_history(const char *path, t_error *errors)
{
	char		*line;
	size_t		i;
	int			fd;

	i = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror_switch(errors, "kiki_history", NULL);
		return (FAILURE);
	}
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("\t%zu %s", i++, line);
		free(line);
	}
	if (close(fd) == FAILURE)
	{
		perror_switch(errors, "kiki_history", NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ms_history(char **args, t_list **envp, void *data)
{
	t_core	*core;
	int		flag;
	int		ret;
	char	*path;

	(void)envp;
	core = (t_core *)data;
	flag = have_flag(args);
	if (flag == FAILURE)
	{
		errno = EINVAL;
		perror_switch(core->errors, "kiki_history", NULL);
		return (errno);
	}
	path = get_path_hist(core->uname, core->errors);
	if (path == NULL)
		return (errno);
	if (flag == 1)
	{
		ret = print_history(path, core->errors);
		return (free(path), ret);
	}
	ret = ft_clear_history(path, core);
	return (free(path), ret);
}
