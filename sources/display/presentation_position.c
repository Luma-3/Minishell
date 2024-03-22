/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presentation_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:19:39 by anthony           #+#    #+#             */
/*   Updated: 2024/03/22 14:45:15 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*handle_position(t_list *env, char *display_message, int last_status)
{
	if (!display_message)
		return (ft_create_prompt(env, last_status));
	// if (diff_position(display_message) == true)
	// {
	// 	free(display_message);
	// 	display_message = ft_create_prompt(env);
	// }
	return (ft_create_prompt(env, last_status));
}
