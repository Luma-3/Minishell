/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 18:16:22 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"

static char	*ft_get_hostname(t_list *env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ms_getenv(env, "LOGNAME");
	if (tmp == NULL)
		tmp = ms_getenv(env, "USER");
	tmp2 = ft_strjoin(tmp, "@");
	free(tmp);
	tmp = ft_strjoin(CYAN, tmp2);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	free(tmp);
	return (tmp2);
}

static char	*ft_get_cwd(t_list *env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ms_getenv(env, "PWD");
	tmp2 = ft_strjoin(BLUE, tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "$> ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, RESET);
	free(tmp);
	return (tmp2);
}

static char	*ft_create_prompt(t_list *env)
{
	char	*display_hostname;
	char	*display_path;
	char	*display_prompt;

	display_hostname = ft_get_hostname(env);
	display_path = ft_get_cwd(env);

	display_prompt = ft_strjoin(display_hostname, display_path);
	free(display_hostname);
	free(display_path);
	return (display_prompt);
}

void	read_input(t_list **env)
{
	char		*input;
	t_prompt	prompt;
	char		*display_message;

	while (true)
	{
		display_message = ft_create_prompt(*env);
		input = readline(display_message);
		if (input != NULL && input[0] != '\0')
		{
			if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			{
				ft_lstclear(env, free);
				rl_clear_history();
				free(input);
				exit(EXIT_SUCCESS);
			}
			ft_add_history(input, *env);
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
	ft_create_history(env);
	presentation_display(&env);
	read_input(&env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL