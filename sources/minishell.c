/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/14 18:24:57 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(void)
{
	char	*prompt;
	int		i;

	i = 0;
	while (true)
	{
		i = 0;
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			printf("prompt = %s\n", prompt);
			printf("nb_words = %d\n", count_words(prompt));
			while(i < (int)ft_strlen(prompt))
			{
				printf("letters = %d\n", count_letters(prompt, i));
				i = place_cursor(prompt, i);
			}
			free(prompt);
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
