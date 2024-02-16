/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 18:10:00 by jbrousse         ###   ########.fr       */
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

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int ac, char **av)
{
	t_list	*env_list;
	char 	**env_test;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE); //TODO prompt error message
	//TODO BEAU
	env_list = copy_env(envp);
	read_input();
	return (EXIT_SUCCESS);
}
