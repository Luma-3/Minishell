/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:28:27 by anthony           #+#    #+#             */
/*   Updated: 2024/04/03 00:29:08 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	pop_stack_to_list(t_dstack *stack, t_list **list)
{
	char	*data;
	int		i;

	while (stack->top != NULL)
	{
		i = 0;
		data = (char *)stack->top->data;
		while (data[i] != '\0')
		{
			if (data[i] == '*')
			{
				return ;
			}
			i++;
		}
		ft_lstadd_back(list, ft_lstnew(d_pop_stk(stack)));
	}
}

void	clean_access_lst(t_list **head, char *start_content)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*free_node;

	tmp = *head;
	(void)start_content;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (access((char *)tmp->content, F_OK) == FAILURE)
		{
			free_node = ft_lstdetach(head, tmp);
			free(free_node->content);
			free(free_node);
		}
		tmp = next;
	}
	if (ft_lstsize(*head) == 0)
		ft_lstadd_front(head, ft_lstnew(start_content));
}