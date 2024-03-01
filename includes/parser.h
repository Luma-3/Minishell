/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:57:07 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:40 by antgabri         ###   ########.fr       */
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

#endif // PARSER_H