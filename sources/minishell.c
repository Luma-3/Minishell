/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/12 15:41:45 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*prompt;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE); //TODO prompt error message
	//TODO BEAU
	while (true)
	{
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			printf("%s ok", prompt);
			free(prompt);
			return (0);
		}
	}
	return (EXIT_SUCCESS);
}
