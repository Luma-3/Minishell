/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/07 17:23:53 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "convention.h"
# include "core_data.h"
# include "libft.h"

# define WEIGHT_CMD 1
# define WEIGHT_PIPE 2
# define WEIGHT_AND 3
# define WEIGHT_OR 3

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_OUT_APPEND 3
# define REDIR_HEREDOC 4

/////////////////////////
////// PRE PARSER //////
/////////////////////////

int			verif_arg(const char *prompt);

/////////////////////////
////// POST PARSER //////
/////////////////////////

int			count_words(const char *prompt);

int			count_letters(const char *start_word);

char		**alloc_tab(char *prompt);

int			post_parser(t_bin_tree	*root);

///////////////////////////
////// ATOMIC PARSER //////
///////////////////////////

int			skip_quote_parenthesis(const char *prompt, int index);

int			create_ats(t_ats *ats);

int			parse_ats(char *prompt, t_ats *ats, bool check_arg);

// bin_tree.c

void		print_inorder(t_bin_tree *root);

t_bin_tree	*create_node(t_token *data);

void		insert_node(t_bin_tree **root, t_token *data,
				int (*cmp)(t_token *, t_token *));

int			compare_token(t_token *data1, t_token *data2);

void		clear_tree(t_bin_tree *root);

// ats_copy_cmd.c

int			copy_pipeline(t_ats *ats, int i_read, int *i_copy, int *nb_redir);

int			copy_cmd_token(t_ats *ats, int *nb_redir, int i_read, int *i_copy);

//////////////////////////
////// PARSER UTILS //////
//////////////////////////

// place_cursor.c

int			place_cursor_parenthesis(const char *prompt, int index);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_after_token(const char *prompt, int i);

// is_type.c

int			is_parenthesis(const char token);

int			is_pipe(const char *prompt, int index);

int			is_token(char token);

int			is_redir_type(const char *prompt, int index);

int			is_quote_type(char c);

#endif // PARSER_H