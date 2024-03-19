/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:44:03 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 18:25:12 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redirection.h"

void	handle_heredoc(const char *prompt, t_ats *ats)
{
	int		i;
	int		j;
	char	*delimiteur;

	i = 0;
	j = 0;
	delimiteur = NULL;
	while (prompt[i])
	{
		if (is_quote(prompt[i]) == true)
			i = place_cursor_quote(prompt, i);
		if (is_redir_type(prompt + i) == REDIR_HEREDOC)
		{
			i += 2;
			i = ft_skip_whitespaces(prompt, i);
			while (prompt[i + j] && ft_iswhitespace(prompt[i + j]) == false)
				j++;
			delimiteur = ft_strndup(prompt + i, j);
			create_enqueue_heredoc(ats->queue_heredoc, delimiteur);
		}
		i++;
	}
}
