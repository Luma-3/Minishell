/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/23 02:16:41 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	ft_putstr_display(t_ats *ats, t_list *env, char *message)
{
	(init_ats(ats, message, env), parse_ats(message, ats, false));
	read_ats(ats, ats->root);
	clear_ats(ats, ATS_HEREDOC | ATS_PIPE
		| ATS_REDIR);
}

int	diff_position(char *display_message)
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
	while (ft_isalpha(display_message[i]) == false && i >= 0)
		i--;
	if (new_position[ft_strlen(new_position) - 1] != display_message[i])
		return (true);	
	return (false);
}

char	*display_prompt(t_list *env, char *display_message, int last_status)
{
	if (diff_position(display_message) == true || display_message == NULL)
	{
		display_message = ft_create_prompt(env, last_status);
		if (display_message == NULL)
			return (ft_strdup("I Lost my prompt 😢\n"));
	}
	ft_putendl_fd(display_message, 1);
	return (display_message);
}

void	presentation_display(t_ats *ats, t_list *env)
{
	ft_putstr_display(ats, env, "toilet -tf future --gay -F border\
			Welcome in KIKISHELL");
	return ;
}

void	goodbye_display(t_ats *ats, t_list *env)
{
	ft_putstr_display(ats, env, "toilet -tf future --gay -F border\
			SEE YOU SOON !!");
	return ;
}
