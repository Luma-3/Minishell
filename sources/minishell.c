/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 18:38:08 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_list *env_list)
{
	char	*prompt;
	char	**tab;

	while (true)
	{
		prompt = readline("minishell > ");
		if (prompt != NULL && prompt[0] != '\0')
		{
			tab = alloc_tab(prompt);
			free(prompt);
			prompt = get_path(tab, env_list);
			if (prompt != NULL)
			{
				exec(tab, prompt, env_list);
			}
		}
	}
}

void	print_env(void *str)
{
	printf("%s\n", (char *)str);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env_list;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE); //TODO prompt error message
	//TODO BEAU
	env_list = copy_env(envp);
	read_input(env_list);
	return (EXIT_SUCCESS);
}
