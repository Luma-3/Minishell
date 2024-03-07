/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presentation_display.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/07 13:31:09 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

int	diff_position(char *display_message)
{
	char	**old_position;
	char	*new_position;

	old_position = ft_split(display_message, '@');
	if (old_position == NULL)
		return (ft_rm_split(old_position), false);
	new_position = malloc(sizeof(char) * 100);
	if (new_position == NULL)
		return (ft_rm_split(old_position), false);
	getcwd(new_position, 100);
	if (ft_strncmp(old_position[1], new_position,
			ft_strlen(old_position[1])) != 0)
	{
		ft_rm_split(old_position);
		return (free(new_position), true);
	}
	ft_rm_split(old_position);
	free(new_position);
	return (false);
}

static char	*ft_get_hostname(t_list *env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ms_getenv(env, "LOGNAME");
	if (tmp == NULL)
		tmp = ms_getenv(env, "USER");
	tmp2 = ft_strjoin(tmp, "@");
	free(tmp);
	tmp = ft_strjoin(BOLD_MAGENTA, tmp2);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	free(tmp);
	return (tmp2);
}

static char	*ft_get_cwd(t_list *env)
{
	char	*tmp;
	char	*tmp2;

	(void)env;
	tmp = malloc(sizeof(char) * 100);
	if (tmp == NULL)
		return (NULL);
	getcwd(tmp, 100);
	tmp2 = ft_strjoin(BOLD_YELLOW, tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, " > ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	free(tmp);
	return (tmp2);
}

char	*ft_create_prompt(t_list *env)
{
	char	*display_hostname;
	char	*display_path;
	char	*display_prompt;

	display_hostname = ft_get_hostname(env);
	display_path = ft_get_cwd(env);
	display_prompt = ft_strjoin(display_hostname, display_path);
	free(display_hostname);
	free(display_path);
	return (display_prompt);
}

// int	presentation_display(t_list **env)
// {
// 	t_prompt	command;

// 	//parser_init(&command,
// 	//	"toilet -tf future --gay -F border Welcome in MINISHELL", env);
// 	launch_child(&command);
// 	ft_rm_split(command.tab);
// 	return (SUCCESS);
// }
