/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kikidoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:03:31 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 15:28:48 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "parser.h"

static char	*create_kikidoc_name(int id)
{
	char	*name;
	char	*id_str;

	id_str = ft_itoa(id);
	if (id_str == NULL)
		return (NULL);
	name = ft_strjoin(".kikidoc_", id_str);
	free(id_str);
	return (name);
}

static char	*get_delimiter(const char *prompt, int index, t_error *errors)
{
	size_t		i;
	char		*delimiter;
	char		*clean_delimiter;

	i = 0;
	index = ft_skip_whitespaces(prompt, index + 2);
	while (prompt[index + i] && ft_iswhitespace(prompt[index + i]) == false)
		i++;
	delimiter = ft_strndup(prompt + index, i);
	if (delimiter == NULL)
		return (NULL);
	if (verif_filename(delimiter, errors) == false)
		return (free(delimiter), NULL);
	if (delimiter[0] == '\0')
	{
		errno = ESYNTAX;
		perror_switch(errors, "kikishell: kikidoc", "newline");
		return (free(delimiter), NULL);
	}
	clean_delimiter = clean_quote(delimiter);
	free(delimiter);
	if (clean_delimiter == NULL)
		return (NULL);
	return (clean_delimiter);
}

t_kikidoc_data	*creat_kikidoc(int id, const char *prompt, int index,
								t_error *errors)
{
	t_kikidoc_data	*kikidoc;

	kikidoc = (t_kikidoc_data *)malloc(sizeof(t_kikidoc_data));
	if (kikidoc == NULL)
		return (NULL);
	kikidoc->delimiter = get_delimiter(prompt, index, errors);
	if (kikidoc->delimiter == NULL)
		return (free_kikidoc(kikidoc), NULL);
	kikidoc->filename = create_kikidoc_name(id);
	if (kikidoc->filename == NULL)
		return (free_kikidoc(kikidoc), NULL);
	return (kikidoc);
}
