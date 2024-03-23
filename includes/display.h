/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthony <anthony@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:41:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/23 02:10:16 by anthony          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parser.h"
# include "exec.h"
# include "env.h"
# include "color.h"

void	presentation_display(t_ats *ats, t_list *env);

char	*ft_create_prompt(t_list *env, int last_status);

int		diff_position(char *display_message);

char	*display_prompt(t_list *env, char *display_message, int last_status);

char	*path_to_tilde(t_list *env);

char	*assemble(char **display);

char	*ft_get_chdir(void);

void	goodbye_display(t_ats *ats, t_list *env);

#endif