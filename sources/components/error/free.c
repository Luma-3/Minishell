/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:13:14 by anthony           #+#    #+#             */
/*   Updated: 2024/04/04 17:15:17 by anthony          ###   ########.fr       */
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
