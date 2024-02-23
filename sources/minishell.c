/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/23 14:15:53 by antgabri         ###   ########.fr       */
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
			if (ft_strncmp(prompt, "exit", ft_strlen(prompt)) == 0)
			{
				ft_lstclear(&env, free);
				free(prompt);
				exit(EXIT_SUCCESS);
			}
			if (verif_arg(prompt) == SUCCESS)
			{
				if (exec(env, prompt) == FAILURE)
					printf("ERROR_FORMAT\n");
			}
			perror("exec");
			free(prompt);
		}
	}
}

static int	presentation_art(t_list *env)
{
	char	*tab;
	pid_t	pid;

	tab = ft_strdup("toilet -t -f future --gay -F border Welcome to MINISHELL");
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (FAILURE);
	}
	else if (pid == 0)
	{
		if (exec_command(tab, env) == FAILURE)
			exit(FAILURE);
		exit(SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (free(tab), SUCCESS);
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
	presentation_art(env);
	read_input(env);
	return (EXIT_SUCCESS);
}
	//TODO prompt error message
	//TODO BEAU
	//FORK DES LE DEBUT POUR LE SIGNAL