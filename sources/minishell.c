/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/27 14:42:30 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_list *env)
{
	char		*input;
	t_prompt	prompt;
	
	while (true)
	{
		input = readline("minishell > ");
		if (input != NULL && input[0] != '\0')
		{
			if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			{
				ft_lstclear(&env, free);
				free(input);
				exit(EXIT_SUCCESS);
			}
			parser_init(&prompt, input, env); // to verify
			launch_child(&prompt); // to verify
			//perror("exec");
			free(input);
		}
	}
}

// static int	presentation_display(t_list *env)
// {
// 	char	*tab;
// 	pid_t	pid;

// 	tab = ft_strdup("toilet -t -f future --gay -F border Welcome in MINISHELL");
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork failed");
// 		return (FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (exec_command(tab, env) == FAILURE)
// 		{
// 			print_error_display();
// 			exit(FAILURE);
// 		}
// 		exit(SUCCESS);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (free(tab), SUCCESS);
// }

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
	//presentation_display(env);
	read_input(env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL