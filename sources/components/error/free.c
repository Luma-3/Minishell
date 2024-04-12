/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:13:14 by anthony           #+#    #+#             */
/*   Updated: 2024/04/12 17:40:08 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "core_data.h"
#include "parser.h"

void	free_data_tree(void *content)
{
	t_token	*data;

	if (!content)
		return ;
	data = (t_token *)content;
	if (data == NULL)
		return ;
	if (data->cmd != NULL)
	{
		free(data->cmd);
		data->cmd = NULL;
	}
	free(data);
	data = NULL;
}
