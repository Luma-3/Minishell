/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 15:53:39 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_sig.h"

void	read_input(t_list **env)
{
	char		*input;
	t_prompt	prompt;

	while (true)
	{
		input = readline("minishell > ");
		if (input == NULL)
		{
			printf("\n");
			ft_lstclear(env, free);
			exit(EXIT_SUCCESS);
		}
		if (input[0] != '\0')
		{
			if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			{
				ft_lstclear(env, free);
				free(input);
				exit(EXIT_SUCCESS);
			}
			if (parser_init(&prompt, input, env) == FAILURE)
			{
				free(input);
				printf("Error quote not close\n");
			}
			else
			{
				launch_child(&prompt);
				ft_rm_split(prompt.tab);
				free(input);
			}
		}
	}
}

static int	presentation_display(t_list **env)
{
	t_prompt	command;

	parser_init(&command,
		"toilet -tf future --gay -F border Welcome in MINISHELL", env);
	launch_child(&command);
	ft_rm_split(command.tab);
	return (SUCCESS);
}

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	printf("\033]0;MINISHELL\007");
	init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	presentation_display(&env);
	read_input(&env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL