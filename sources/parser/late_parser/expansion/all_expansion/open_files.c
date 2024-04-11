/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:29:50 by anthony           #+#    #+#             */
/*   Updated: 2024/04/11 11:31:50 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "stackft.h"

int	open_files(t_dstack *stack, t_match_file *match_file, t_list **lst, int i)
{
	DIR				*dir;
	t_list			*tmp;

	if (match_file == NULL || match_file->path == NULL)
		return (FAILURE);
	dir = opendir(match_file->path);
	if (dir == NULL)
		return (FAILURE);
	if (find_files(stack, match_file, dir, i) == false)
	{
		tmp = ft_lstnew(match_file->old_data);
		if (tmp != NULL)
			ft_lstadd_front(lst, tmp);
		closedir(dir);
		return (FAILURE);
	}
	free(match_file->old_data);
	if (closedir(dir) == -1)
		return (FAILURE);
	return (SUCCESS);
}
