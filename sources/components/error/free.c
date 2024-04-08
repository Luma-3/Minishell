/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:13:14 by anthony           #+#    #+#             */
/*   Updated: 2024/04/08 12:08:59 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "core_data.h"
#include "parser.h"

void	free_data_tree(void *content)
{
	t_token	*data;

	data = (t_token *)content;
	if (data->cmd != NULL)
		free(data->cmd);
	free(data);
}
