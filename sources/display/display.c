/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/24 17:37:17 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

// static void	ft_putstr_display(t_ats *ats, t_list *env, char *message)
// {	
// 	t_ats	ats_display;

// 	clear_ats(ats, ATS_REDIR | ATS_ROOT | ATS_PROMPT | ATS_HEREDOC | ATS_PIPE);
// 	init_ats(&ats_display, message, env);
// 	parse_ats(message, &ats_display, true);
// 	read_ats(&ats_display, ats_display.root);
// 	ats = &ats_display;
// }

void	presentation_display(t_ats *ats, t_list *env)
{
	char *command;

	command = ft_strdup("toilet -tf future --gay -F border\
			Welcome in KIKISHELL");
	init_ats(ats, command, env);
	parse_ats(command, ats, false);
	read_ats(ats, ats->root);
	ft_putchar_fd('\n', 1);
	return ;
}

void	goodbye_display(t_list *env)
{
	char *command;
	t_ats ats;

	command = ft_strdup("See you soon !!!");
	init_ats(&ats, command, env);
	parse_ats(command, &ats, false);
	read_ats(&ats, ats.root);
	ft_putchar_fd('\n', 1);
	return ;
}

static int	diff_position(char *display_message)
{
	char	*new_position;
	int		i;

	new_position = NULL;
	if (display_message == NULL)
		return (true);
	i = ft_strlen(display_message);
	new_position = getcwd(new_position, 0);
	if (new_position == NULL)
		return (false);
	while (ft_isalnum(display_message[i]) == false && i >= 0)
		i--;
	if (new_position[ft_strlen(new_position) - 1] != display_message[i])
		return (true);	
	return (false);
}

char	*display_prompt(t_ats *ats, t_list *env, char *display_message)
{
	if (diff_position(display_message) == true || display_message == NULL)
	{
		display_message = ft_create_prompt(env, ats->last_status);
		if (display_message == NULL)
			return (ft_strdup("I Lost my prompt 😢\n"));
	}
	ft_putendl_fd(display_message, 1);
	// clear_ats(ats, ATS_PROMPT | ATS_REDIR | ATS_ROOT | ATS_PIPE | ATS_HEREDOC);
	return (display_message);
}
