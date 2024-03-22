/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:41:17 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/22 14:46:31 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "minishell.h"
# include "parser.h"
# include "exec.h"
# include "env.h"
# include "color.h"

int		presentation_display(t_ats *ats, t_list **env);

char	*ft_create_prompt(t_list *env, int last_status);

int		diff_position(char *display_message);

char	*handle_position(t_list *env, char *display_message, int last_status);

char	*get_home_path(t_list *env, char *old_path);
char	*ft_get_cwd(t_list *env);
char	*ft_get_chdir(void);
char	*display_error(int last_status);




#endif