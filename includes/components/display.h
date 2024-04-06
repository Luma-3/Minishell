/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:41:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/04/06 22:05:02 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parser.h"
# include "exec.h"
# include "environement.h"
# include "color.h"

void	display_msg(t_maindata *core_data, char *msg);

char	*create_sh_prompt(t_list *env, char *uname, int last_status);

char	*shell_prompt(t_maindata *core_data);

char	*path_to_tilde(t_list *env);

char	*assemble(char **display);

char	*get_current_dir(void);

#endif