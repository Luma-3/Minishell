/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/04 17:14:30 by jbrousse         ###   ########.fr       */
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

#define WEIGHT_REDIR 0
#define WEIGHT_CMD 1
#define WEIGHT_AND 3
#define WEIGHT_OR 3
#define WEIGHT_PIPE 2

typedef struct s_redir
{
	char	*file;
	int		type;
	int		fd;
}			t_redir;

typedef	struct s_token
{
	char	*cmd;
}			t_token;
typedef union u_tree_data
{
	t_token	*token;
	t_redir	*redir;
}			t_tree_data;

typedef struct s_bin_tree
{
	union u_tree_data		data;
	struct s_bin_tree	*left;
	struct s_bin_tree	*right;
}						t_bin_tree;



void	print_inorder(t_bin_tree *root);

t_bin_tree	*create_node(union u_tree_data data);

void	insert_node(t_bin_tree **root, union u_tree_data data, int (*cmp)(union u_tree_data, union u_tree_data));

int	compare_token(union u_tree_data data1, union u_tree_data data2);

t_bin_tree	*read_line(const char *prompt, int *index_read);

int is_pipe(const char *prompt, int index);

t_bin_tree	*create_ats(t_bin_tree **root, const char *prompt, int index_offset);

void	copy_token(const char *prompt, t_bin_tree **root, int start, int end);

void	clear_tree(t_bin_tree *root);

#endif // PARSER_H