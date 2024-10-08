/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/15 12:09:24 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "core_data.h"
# include "ms_error.h"
# include "stackft.h"
# include <dirent.h>
# include <sys/stat.h>

# define WEIGHT_CMD 1
# define WEIGHT_AND 2
# define WEIGHT_OR 2

typedef struct s_match_file
{
	char		*prefix;
	char		*suffix;
	char		*path;
	char		*old_data;
}				t_match_file;

/////////////////////////
////// PRE PARSER //////
/////////////////////////

int				verif_prompt(const char *prompt, t_error *errors);

int				verif_if_quote_closed(const char *prompt, t_error *errors);

int				verif_if_parenthesis_closed(const char *prompt,
					t_error *errors);

int				verif_arg_parenthesis(const char *prompt, t_error *errors);

int				verif_token_separation(const char *prompt, t_error *errors);

int				verif_before_operator(const char *prompt, char *token);

int				verif_token_before(const char *prompt, int i);

int				verif_token_after(const char *prompt, int i);

bool			verif_filename(char *filename, t_error *errors);

/////////////////////////
////// POST PARSER //////
/////////////////////////

long			count_letters(const char *start_word);

char			**list_to_tab(t_list **lst);

char			**late_parser(t_core *core_data, t_ast *node);
// clean

char			*clean_quote(char *word);

///////////////////////////
////// ATOMIC PARSER //////
///////////////////////////

int				parse_prompt(char *prompt, t_core *core_data,
					bool check_arg);

int				atomize_prompt(t_core *ats);

// bin_tree.c

t_ast			*create_node(t_token *data);

int				insert_node(t_ast **root, t_token *data,
					int (*cmp)(t_token *, t_token *));

int				compare_token(t_token *data1, t_token *data2);

void			clear_tree(t_ast *root, void (*free_data)(void *));

size_t			count_nodes(t_ast *root, size_t count);

// ats_copy_cmd.c

int				copy_cmd_operator(t_core *ats, int *i_copy, int *i_read);

t_token			*copy_token(t_core *core, const char *prompt,
					size_t len_copy);

t_token			*copy_insert_node(t_core *ats, int i_copy, int i_read);

// take_redir.c

char			*take_redir(t_core *ats, const char *prompt, int *nb_redir);

//////////////////////////
////// PARSER UTILS //////
//////////////////////////

// place_cursor.c

int				place_cursor_parenthesis(const char *prompt, int index);

int				place_cursor_quote(const char *prompt, int i);

int				place_cursor_after_token(const char *prompt, int i);

int				skip_quote_parenthesis(const char *prompt, int index);

// is_type.c

bool			is_pipe(const char *prompt);

bool			is_operator(const char *token);

int				is_redir_type(const char *prompt);

bool			is_quote(const char c);

//is_type2.c

bool			is_subshell(const char *cmd);

bool			is_pipeline(const char *prompt);

bool			valid_env_char(const char c);

//check_char.c

char			check_quote(char quote, char c);

int				check_parenthesis(char parenthesis);
//////////////////////////
/////// EXPANSION  ///////
//////////////////////////

int				expansion_cmd(t_core *core_data, t_list **args);

// expansion_env

char			*handle_env(t_core *core_data, const char *arg);

char			*copy_data_env(t_core *core_data, char *arg, int index);

// expansion_tilde

char			*handle_tilde(const char *arg, const char *uname);

char			*copy_data_tilde(const char *uname, char *arg, int index);

bool			check_tilde(const char *arg, const int prev_i,
					const int next_i);

// expansion_all

t_list			*get_all_file(t_list **head, t_list *arg);

void			rec_all(t_dstack *stack, t_list **list);

void			free_match_file(t_match_file *match_file);
// get_infos

char			*get_token(char *prefix, char *suffix);

char			*get_suffix(char *prompt, int index);

char			*get_prefix(char *prompt, int index);

char			*get_path_wildcard(char *arg, int index);

char			*get_replace_token(t_match_file *match_file, t_dstack *stack);

// find_files

bool			find_files(t_dstack *stack, t_match_file *match_file, DIR *dir,
					int i);

bool			find_match_file(char *entry, char *prefix, char *suffix);

bool			get_last_suffix(char *suffix, char *entry, int j, int i);

// open_file

int				open_files(t_dstack *stack, t_match_file *match_file,
					t_list **lst, int i);

// decision.c

bool			final_decision(char *entry, char *suffix);

bool			decision_file(char *entry, char *suffix);

bool			decision_directory(char *entry, char *suffix);

bool			verif_suffix_ptr(char *entry, char *suffix, int i);

// utils

t_match_file	*init_match_file(t_match_file *match_file,
					char *data, int i);

void			no_access_file(t_dstack *stack, t_list **list,
					t_match_file *match_file);

bool			only_all(char *suffix);

int				ft_findstr(char *str, char *to_find, int i);

char			*file_to_directory(t_match_file *match_file, char *file_name);

// lst_utils

void			clean_access_lst(t_list **head, char *start_content);

void			pop_stack_to_list(t_dstack *stack, t_list **list);

#endif // PARSER_H