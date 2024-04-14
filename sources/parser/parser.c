/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:22:25 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 14:57:56 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

int	parse_prompt(char *prompt, t_core *core_data, bool check_arg)
{
	char	*tmp;

	tmp = ft_strtrim(prompt, " /t/n/r/v/f");
	if (tmp == NULL)
		return (FAILURE);
	if (tmp[0] == '\0')
		return (free(tmp), FAILURE);
	free(tmp);
	if (check_arg == true)
	{
		if (verif_prompt(prompt, core_data->errors) == FAILURE)
			return (FAILURE);
		if (handle_kikidoc(prompt, core_data) == FAILURE)
			return (FAILURE);
	}
	if (atomize_prompt(core_data) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
