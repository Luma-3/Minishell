/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:39:34 by antgabri          #+#    #+#             */
/*   Updated: 2024/03/22 14:45:00 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*get_home_path(t_list *env, char *old_path)
{
	char	*home;
	char	*new_path;
	int		i;
	int		len;

	i = 0;
	home = ms_getenv(env, "HOME");
	if (home == NULL)
		return (old_path);
	while (old_path[i] == home[i]
		&& old_path[i] != '\0' && home[i] != '\0')
		i++;
	len = ft_strlen(old_path) - i;
	new_path = malloc(sizeof(char) * len);
	if (new_path == NULL)
		return (old_path);
	free(home);
	ft_strlcpy(new_path, old_path + i, len + 1);
	home = ft_strjoin(" ~", new_path);
	free(new_path);
	return (home);
}

char	*ft_get_cwd(t_list *env)
{
	char	*tmp;
	char	*tmp2;
	int		len;
	int		size_cwd;

	tmp = malloc(sizeof(char) * 100);
	if (tmp == NULL)
		return (ft_strdup(" > "));
	tmp = getcwd(tmp, 100);
	if (tmp == NULL)
		return (free(tmp), ft_strdup(" > "));
	len = ft_strlen(tmp);
	size_cwd = ft_strlen(tmp);
	while (len >= 0 && tmp[len] != '/')
		len--;
	tmp2 = ft_strndup(tmp, size_cwd - (size_cwd - len));
	free(tmp);
	tmp = get_home_path(env, tmp2);
	free(tmp2);
	return (tmp);
}

char	*ft_get_chdir(void)
{
	char	*tmp;
	char	*tmp2;
	int		len;
	int		size_cwd;

	tmp = malloc(sizeof(char) * 100);
	if (tmp == NULL)
		return (ft_strdup(" > "));
	tmp = getcwd(tmp, 100);
	if (tmp == NULL)
		return (free(tmp), ft_strdup(" > "));
	len = ft_strlen(tmp);
	size_cwd = ft_strlen(tmp);
	while (len >= 0 && tmp[len - 1] != '/')
		len--;
	tmp2 = ft_strndup(tmp + len, size_cwd);
	free(tmp);
	return (tmp2);
}

char	*display_error(int last_status)
{
	char	*display_error;

	if (last_status == 0)
		display_error = ft_strdup(" ☀️  ");
	else
		display_error = ft_strdup(" 🌙 ");
	return (display_error);
}
