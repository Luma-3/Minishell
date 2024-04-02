/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/02 12:17:45 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"
# include "stackft.h"

# include <stdbool.h>

# define WEIGHT_CMD 1
# define WEIGHT_AND 2
# define WEIGHT_OR 2

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_OUT_APPEND 3
# define REDIR_HEREDOC 4

typedef struct s_match_file
{
	char		*prefix;
	char		*suffix;
	char		*path;
}				t_match_file;

/////////////////////////
////// PRE PARSER //////
/////////////////////////

int			verif_prompt(const char *prompt);

int			verif_if_quote_closed(const char *prompt);

int			verif_if_parenthesis_closed(const char *prompt);

int			verif_arg_parenthesis(const char *prompt);

int			verif_before_operator(const char *prompt, char *token);

int			verif_token_separation(const char *prompt);

int			verif_before_operator(const char *prompt, char *token);

void		handle_heredoc(const char *prompt, t_maindata *ats);

/////////////////////////
////// POST PARSER //////
/////////////////////////

int			count_words(const char *prompt);

int			count_letters(const char *start_word);

char		**list_to_tab(t_list **lst);

char		**late_parser(t_maindata *core_data, t_ats *node);
// clean

char		*clean_quote(char *word);

///////////////////////////
////// ATOMIC PARSER //////
///////////////////////////

int			init_core_data(t_maindata *ats, char *prompt, t_list *env);

int			parse_prompt(char *prompt, t_maindata *core_data, bool check_arg);

int			atomize_prompt(t_maindata *ats);

// bin_tree.c

t_ats		*create_node(t_token *data);

int			insert_node(t_ats **root, t_token *data,
				int (*cmp)(t_token *, t_token *));

int			compare_token(t_token *data1, t_token *data2);

void		clear_tree(t_ats *root, void (*free_data)(void *));

size_t		count_nodes(t_ats *root, size_t count);

// ats_copy_cmd.c

int			copy_cmd_operator(t_maindata *ats, int *i_copy, int *i_read);

t_token		*copy_token(t_maindata *ats, const char *prompt, int size_copy);

t_token		*copy_insert_node(t_maindata *ats, int i_copy, int i_read);

// take_redir.c

char		*take_redir(t_maindata *ats, const char *prompt, int size_prompt,
				int *nb_redir);

//////////////////////////
////// PARSER UTILS //////
//////////////////////////

// place_cursor.c

int			place_cursor_parenthesis(const char *prompt, int index);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_quote(const char *prompt, int i);

int			place_cursor_after_token(const char *prompt, int i);

int			place_cursor_before_prefix(const char *prompt, int index);

int			skip_quote_parenthesis(const char *prompt, int index);

int			skip_single_quote(char *str, int i);

// is_type.c

int			is_parenthesis(const char token);

int			is_pipe(const char *prompt);

int			is_operator(const char *token);

int			is_redir_type(const char *prompt);

int			is_quote(const char c);

//is_type2.c

bool		is_subshell(const char *cmd, int size_cmd);

bool		is_pipeline(const char *prompt);

bool		is_valid_char_name_env(const char c);

//////////////////////////
/////// EXPANSION  ///////
//////////////////////////
// TODO Trie par fichier

int			expansion_cmd(t_maindata *core_data, t_list **args);

char		*copy_data_env(t_maindata *core_data, char *arg, int index);

char		*copy_data_tilde(const char *uname, char *arg, int index);

bool		check_tilde(const char *arg, const int prev_i,
				const int next_i);

t_list		*get_all_file(t_list **head, t_list *arg);

//all_utils.c
char		*get_token(char *prefix, char *suffix);

char		*get_suffix(char *prompt, int index);

char		*get_prefix(char *prompt, int index);

char		*get_path_wildcard(char *arg, int index);

bool		find_match_file(char *entry, char *prefix, char *suffix);

void		rec_all(t_dstack *stack, t_list **list);

char		*handle_tilde(const char *arg, const char *uname);

char		*handle_env(t_maindata *core_data, const char *arg);


#endif // PARSER_H