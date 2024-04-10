/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:22:25 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/10 23:31:52 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_prompt(char *prompt, t_maindata *core_data, bool check_arg)
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
		if (handle_heredoc(prompt, core_data) == FAILURE)
			return (FAILURE);
	}
	if (atomize_prompt(core_data) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
