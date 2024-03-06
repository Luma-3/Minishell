/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/06 10:56:11 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "convention.h"
# include "libft.h"

/**
 * @brief Count the number of words in a string
 * 
 * @return the number of words
*/
int			count_words(const char *prompt);

/**
 * @brief Count the number of letters in a word
 * 
 * @return the number of letters
*/
int			count_letters(const char *prompt, int i);

/**
 * @brief Place the cursor at the start of the next word
*/
int			place_cursor_after_word(const char *prompt, int i);

/**
 * @brief Place the cursor at the start of the next quote
*/
int			place_cursor_after_quote(const char *prompt, int i);

/**
 * @brief Place the cursor at the start of the next token
*/
int	 		place_cursor_after_token(const char *prompt, int i);
/**
 * @brief Malloc le double tableau de char
 * 
 * @return NULL if alloc failed pointer on tab if alloc success
*/
char		**alloc_tab(char *prompt);

/**
 * @brief Test if char is a quote type (double quote or single quote)
 * 
 * @param c char to test
 * @return true if is quote type, false is isn't quote type
*/
int			isquote_type(char c);

/**
 * @brief Verifie si les quotes du debut se ferment bien dans la suite de 
 * la chaine
*/
int			verif_quote_delimiter(const char *prompt, char delimiter, int i);

int			verif_arg(char *prompt);



//////////////////////////////  NEW_PARSER  //////////////////////////////////////////
//////////////// WARNING: THIS PART IS NOT COMPLETED YET /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#define WEIGHT_CMD 1
#define WEIGHT_PIPE 2
#define WEIGHT_AND 3
#define WEIGHT_OR 3

#define REDIR_IN 1
#define REDIR_OUT 2
#define REDIR_OUT_APPEND 3
#define REDIR_HEREDOC 4

typedef	struct s_token
{
	int		nb_redir;
	char	*cmd;
}			t_token;

typedef struct s_bin_tree
{
	t_token				*data;
	struct s_bin_tree	*left;
	struct s_bin_tree	*right;
}						t_bin_tree;

typedef	struct s_ats
{
	t_bin_tree	*root;
	t_queue		*queue;
}				t_ats;

// queue

typedef struct s_queue_redir
{
	int		key;
	int		type_redir;
	char 	*file_name;
}			t_queue_redir;

/// read_line.c

void	take_part_to_ats(const char *prompt, t_bin_tree **root, int start, int end);

t_ats	*read_line(const char *prompt, t_ats *ats);

// read_line_utils.c

int place_cursor_after_parenthesis(const char *prompt, int index);

int	is_parenthesis(const char token);

int is_pipe(const char *prompt, int index);

int is_token(char token);

// bin_tree.c

void	print_inorder(t_bin_tree *root);

t_bin_tree	*create_node(t_token *data);

void	insert_node(t_bin_tree **root, t_token *data, int (*cmp)(t_token *, t_token *));

int	compare_token(t_token *data1, t_token *data2);

void	clear_tree(t_bin_tree *root);

// ats.c

void	create_ats(const char *prompt, t_ats *ats);

#endif // PARSER_H