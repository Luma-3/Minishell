/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:01:25 by jbrousse          #+#    #+#             */
/*   Updated: 2024/02/16 17:53:49 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "norm.h"

/**
 * @brief Copy the envp into a t_list.
 * 
 * @param envp The envp to copy
 * 
 * @return The copy of the envp into a t_list.
*/
t_list	*copy_env(char **envp);

/**
 * @brief Transform the env list into a char **.
 * 
 * @param env_lst The env list
 * 
 * @return The copy of the env list into a char **.
*/
char	**env_to_tab(t_list *env_lst);

/**
 * @brief Get the env value from the env list
 * 
 * @param env The env list
 * @param name The name of the env variable
 * 
 * @return The copy value of the env variable.
*/
char	*ms_getenv(t_list *env, const char *name);

/**
 * @brief Set the env value from the env list. If the variable does not exist,
 * it will be created.
 * 
 * @param env The env list
 * @param name The name of the env variable
 * @param value The value of the env variable
 * 
 * @return SUCCESS if the variable has been set, FAILURE otherwise.
*/
int		ms_setenv(t_list *env, const char *name, const char *value);

#endif