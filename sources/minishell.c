/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/03 16:53:11 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

static void	ft_exit(t_list *env, char *input, char *display_message)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		ft_lstclear(&env, free);
		rl_clear_history();
		free(input);
		free(display_message);
		exit(EXIT_SUCCESS);
	}
	return ;
}

void	read_input(t_list **env)
{
	char		*input;
	t_prompt	prompt;
	char		*display_message;

	display_message = NULL;
	while (true)
	{
		display_message = handle_position(*env, display_message);
		input = readline(display_message);
		if (input != NULL && input[0] != '\0')
		{
			ft_exit(*env, input, display_message);
			ft_add_history(input, *env);
			if (parser_init(&prompt, input, env) == FAILURE)
				perror("Minishell error");
			else
			{
				launch_child(&prompt);
				ft_rm_split(prompt.tab);
			}
			free(input);
		}
	}
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
	ft_create_history(env);
	presentation_display(&env);
	read_input(&env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL