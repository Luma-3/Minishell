/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/21 13:40:03 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_list *env_list)
{
	char	*prompt;

	while (true)
	{
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			if (verif_arg(prompt) == SUCCESS)
				exec(env_list, prompt);
			free(prompt);
		}
	}
}

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int ac, char **av, char **envp)
{
	printf("LAUNCHED\n");
	t_list	*env_list;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE); //TODO prompt error message
	//TODO BEAU
	//FORK DES LE DEBUT POUR LE SIGNAL
	env_list = copy_env(envp);
	read_input(env_list);
	return (EXIT_SUCCESS);
}
