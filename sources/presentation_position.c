/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presentation_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:19:39 by anthony           #+#    #+#             */
/*   Updated: 2024/03/03 11:27:57 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_position(t_list *env, char *display_message)
{
	if (!display_message)
		return (ft_create_prompt(env));
	if (diff_position(display_message) == true)
	{
		free(display_message);
		display_message = ft_create_prompt(env);
	}
	return (display_message);
}
