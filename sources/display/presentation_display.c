/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presentation_display.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:20:41 by anthony           #+#    #+#             */
/*   Updated: 2024/03/22 15:05:50 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

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

static char	*assemble(char **display, int nb_display)
{
	char	*display_final;
	char	*tmp;
	int		i;

	i = 0;
	display_final = ft_strdup("");
	while (i < nb_display)
	{
		tmp = ft_strjoin(display_final, display[i]);
		free(display_final);
		display_final = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	free(display[4]);
	free(display[9]);
	free(display[15]);
	free(display[17]);
	return (display_final);
}

char	*ft_create_prompt(t_list *env, int last_status)
{
	char	*display[20];

	display[0] = "\033[1;32m┏━\033[0m";
	display[1] = BG_BLACK_INV;
	display[2] = BOLD_GREEN;
	display[3] = " ";
	display[4] = ms_getenv(env, "LOGNAME");
	display[5] = " 😃 ";
	display[6] = RESET;
	display[7] = BG_BLACK;
	display[8] = BOLD_BLUE;
	display[9] = ft_get_cwd(env);
	display[10] = " ";
	display[11] = RESET;
	display[12] = BG_BLACK_INV;
	display[13] = BOLD_BLUE;
	display[14] = " ";
	display[15] = ft_get_chdir();
	display[16] = " ";
	display[17] = display_error(last_status);
	display[18] = RESET;
	display[19] = NULL;
	return (assemble(display, 19));
}

int	presentation_display(t_ats *ats, t_list **env)
{
	char	*command;

	command = ft_strdup("toilet -tf future --gay -F border Welcome in KIKISHELL");
	init_ats(ats, command, *env);
	parse_ats(command, ats, false);
	read_ats(ats, ats->root);
	return (SUCCESS);
}
