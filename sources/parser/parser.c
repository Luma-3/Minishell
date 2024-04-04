/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:22:25 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/04 16:59:57 by jbrousse         ###   ########.fr       */
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
		if (verif_prompt(prompt) == FAILURE)
			return (FAILURE);
		handle_heredoc(prompt, core_data);
	}
	if (atomize_prompt(core_data) == FAILURE)
	{
		perror("atomize_prompt");
		return (FAILURE);
	}
	return (SUCCESS);
}
