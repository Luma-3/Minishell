/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:41:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/26 14:58:17 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parser.h"
# include "exec.h"
# include "environement.h"
# include "color.h"

void	presentation_display(t_maindata *ats, t_list *env);

void	goodbye_display(t_maindata *ats, t_list *env);

void	ft_create_prompt(t_list *env, int last_status);

char	*path_to_tilde(t_list *env);

char	*assemble(char **display);

char	*ft_get_chdir(void);

#endif