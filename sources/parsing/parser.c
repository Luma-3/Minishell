/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:24:41 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 15:25:12 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static int	count_pattern_tab(char **tab, char *pattern)
{
	int	count;
	int	i;
	int	size_pattern;

	i = 0;
	count = 0;
	size_pattern = ft_strlen(pattern);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], pattern, size_pattern + 1) == 0)
			count++;
		i++;
	}
	return (count);
}

// static void print_prompt(t_prompt *prompt)
// {
// 	int i;

// 	i = 0;
// 	while (prompt->tab[i])
// 	{
// 		printf("tab[%d] = %s\n", i, prompt->tab[i]);
// 		i++;
// 	}
// 	printf("prompt = %s\n", prompt->prompt);
// 	printf("nb_pipe = %d\n", prompt->nb_pipe);
// }

int	parser_init(t_prompt *prompt, char *input, t_list **env)
{
	prompt->tab = alloc_tab(input);
	if (prompt->tab == NULL)
		return (FAILURE);
	prompt->prompt = input;
	prompt->current_index = 0;
	prompt->nb_pipe = count_pattern_tab(prompt->tab, "|");
	prompt->nb_cmd = count_pattern_tab(prompt->tab, "||"); 
	prompt->nb_cmd += count_pattern_tab(prompt->tab, "&&"); 
	prompt->nb_cmd += prompt->nb_pipe + 1;
	prompt->env = env;
	prompt->pos_after_token = 0;
	prompt->input_redir = false;
	//print_prompt(prompt);
	return (SUCCESS);
}
