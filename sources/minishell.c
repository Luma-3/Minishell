/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:11:26 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 11:13:06 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_sig.h"
#include "parser.h"

// void	print_tree(WINDOW *win, t_bin_tree *root, int y, int x, int depth) {
// 	if (root == NULL) return;

// 	// Affiche le nœud actuel
// 	mvwprintw(win, y, x, "%s", root->data.token->cmd);

// 	// Affiche les enfants (gauche et droit)
// 	if (root->left != NULL) {
// 		mvwaddch(win, y + 1, x - depth, '/');
// 		print_tree(win, root->left, y + 2, x - depth - 1, depth / 2);
// 	}
// 	if (root->right != NULL) {
// 		mvwaddch(win, y + 1, x + depth, '\\');
// 		print_tree(win, root->right, y + 2, x + depth + 1, depth / 2);
// 	}
// }

static void init_ats(t_ats *ats, char *prompt) 
{
	t_queue	*queue;
	t_bin_tree	*root;

	root = NULL;
	queue = ft_init_queue();
	ats->prompt = prompt;
	ats->queue = queue;
	ats->root = root;
}

void	read_input(t_list **env)
{
	char		*input;
	t_ats		ats;

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
			init_ats(&ats, input);
			ft_add_history(input, *env);
			if (verif_arg(input) == FAILURE)
				free(input);
			else
			{
			// if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
			// {
			// 	ft_lstclear(env, free);
			// 	rl_clear_history();
			// 	free(input);
			// 	exit(EXIT_SUCCESS);
			// }
			// if (parser_init(&prompt, input, env) == FAILURE)
			// {
			// 	free(input);
			// 	printf("Error quote not close\n");
			// }
			// else
			// {
			// 	launch_child(&prompt);
			// 	ft_rm_split(prompt.tab);
			// 	free(input);
			// }
			// initscr();
			// curs_set(FALSE);
			// WINDOW *win = newwin(100, 100, 0, 0);
			create_ats(&ats);
			//print_tree(win, ats.root, 1, 60, 8);
			// wrefresh(win);
			// getch();
			// delwin(win);
			// endwin();
			// refresh();
			print_inorder(ats.root);
			clear_tree(ats.root);
			ft_clear_queue(ats.queue, free);
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

#include "redirection.h"

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	printf("\033]0;MINISHELL\007");
	//init_signal();
	if (ac != 1)
		return (EXIT_FAILURE);
	env = copy_env(envp);
	ft_create_history(env);
	presentation_display(&env);
	read_input(&env);
	return (EXIT_SUCCESS);
}
	//FORK DES LE DEBUT POUR LE SIGNAL