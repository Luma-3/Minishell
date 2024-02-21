/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monsieurc <monsieurc@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/22 00:36:05 by monsieurc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_list *env)
{
	char	*prompt;

	while (true)
	{
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			if (strcmp(prompt, "exit") == 0)
			{
				free(prompt);
				break ;
			}
			if (verif_arg(prompt) == SUCCESS)
			{
				if (exec(env, prompt) == FAILURE)
					printf("ERROR_FORMAT\n");
			}
			free(prompt);
			perror("End prompt");
		}
	}
}

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	read_input(env);
	return (EXIT_SUCCESS);
}
	//TODO prompt error message
	//TODO BEAU
	//FORK DES LE DEBUT POUR LE SIGNAL