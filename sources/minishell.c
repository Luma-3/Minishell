/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 18:00:05 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(void)
{
	char	*prompt;
	int		i;
	char	**tab;

	i = 0;
	while (true)
	{
		i = 0;
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			tab = alloc_tab(prompt);
			free(prompt);
			while (tab[i])
			{
				printf("%s\n", tab[i]);
				i++;
			}
			prompt = get_path(tab);
			if (prompt != NULL)
			{
				
			}
				printf("%s\n", prompt);
		}
	}
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE); //TODO prompt error message
	//TODO BEAU
	read_input();
	return (EXIT_SUCCESS);
}
