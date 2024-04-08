/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:28:27 by anthony           #+#    #+#             */
/*   Updated: 2024/04/08 12:41:15 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	pop_stack_to_list(t_dstack *stack, t_list **list)
{
	char	*data;
	char	*tmp;
	t_list	*new_node;
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
		tmp = d_pop_stk(stack);
		new_node = ft_lstnew(tmp);
		if (new_node != NULL)
			ft_lstadd_back(list, new_node);
		else
			free(tmp);
	}
}

void	clean_access_lst(t_list **head, char *start_content)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*free_node;
	t_list	*new_node;

	tmp = *head;
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
	{
		new_node = ft_lstnew(start_content);
		if (new_node != NULL)
			ft_lstadd_front(head, new_node);
		return ;
	}
	free(start_content);
}
