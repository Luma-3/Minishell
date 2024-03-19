/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/19 18:18:25 by jbrousse         ###   ########.fr       */
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

void		handle_heredoc(const char *prompt, t_ats *ats);

/////////////////////////
////// POST PARSER //////
/////////////////////////

int			count_words(const char *prompt);

int			count_letters(const char *start_word);

char		**alloc_tab(char *prompt);

int			post_parser(t_bin_tree	*root);

// clean

char		*clean_redir(char *word);

char		*clean_quote(char *word);

///////////////////////////
////// ATOMIC PARSER //////
///////////////////////////

int			skip_quote_parenthesis(const char *prompt, int index);

int			parse_ats(char *prompt, t_ats *ats, bool check_arg);

// bin_tree.c

t_bin_tree	*create_node(t_token *data);

void		insert_node(t_bin_tree **root, t_token *data,
				int (*cmp)(t_token *, t_token *));

int			compare_token(t_token *data1, t_token *data2);

void		clear_tree(t_bin_tree *root);

size_t		count_nodes(t_bin_tree *root, size_t count);

// ats_copy_cmd.c

int			copy_cmd_operator(t_ats *ats, int *i_copy, int *i_read);

t_token		*copy_token(t_ats *ats, const char *prompt, int size_copy);

// take_redir.c

char		*take_redir(t_ats *ats, const char *prompt, int size_prompt,
				int *nb_redir);

//////////////////////////
////// PARSER UTILS //////
//////////////////////////

// place_cursor.c

int			place_cursor_parenthesis(const char *prompt, int index);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_after_token(const char *prompt, int i);

int			skip_quote_parenthesis(const char *prompt, int index);

// is_type.c

int			is_parenthesis(const char token);

int			is_pipe(const char *prompt);

int			is_operator(const char *token);

int			is_redir_type(const char *prompt);

int			is_quote(const char c);

//is_type2.c

bool		is_subshell(const char *cmd, int size_cmd);

bool		is_pipeline(const char *prompt);

#endif // PARSER_H