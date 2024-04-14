/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrousse <jbrousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:34 by jbrousse          #+#    #+#             */
/*   Updated: 2024/04/14 15:47:07 by jbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"
#include "environement.h"
#include "parser.h"
#include <limits.h>

static int	cmp_lst(void *a, void *b)
{
	char	lower_a;
	char	lower_b;

	while (*(char *)a && *(char *)b)
	{
		lower_a = ft_tolower(*(char *)a);
		lower_b = ft_tolower(*(char *)b);
		if (lower_a != lower_b)
			return (lower_a - lower_b);
		a++;
		b++;
	}
	return (0);
}

static void	*dup_content(void *content)
{
	return (ft_strdup((char *)content));
}

static void	print_export(t_list *envp)
{
	t_list	*copy;
	t_list	*iterator;

	copy = ft_lstmap(envp, &dup_content, &free);
	ft_lstsort(&copy, &cmp_lst);
	iterator = copy;
	while (iterator)
	{
		printf("declare -x %s\n", (char *)iterator->content);
		iterator = iterator->next;
	}
	ft_lstclear(&copy, &free);
}

static int	export_var(char *arg, char *name, t_list **envp)
{
	char	*value;
	int		ret;

	if (is_valid_name(name) == false)
	{
		printf("Kikishell: export: '%s': not a valid identifier\n", arg);
		free(name);
		return (1);
	}
	value = get_value(arg);
	if (value == NULL && errno != 0)
	{
		free(name);
		return (errno);
	}
	else if (value != NULL)
	{
		ret = ms_setenv(envp, name, value);
		free(value);
		free(name);
	}
	return (ret);
}

int	ms_export(char **args, t_list **envp, void *data)
{
	int		i;
	int		ret;
	char	*name;

	i = 1;
	ret = 0;
	(void)data;
	if (args[1] == NULL)
	{
		print_export(*envp);
		return (0);
	}
	while (args[i])
	{
		name = get_name(args[i]);
		if (name == NULL)
			return (errno);
		ret = export_var(args[i], name, envp);
		i++;
	}
	return (ret);
}
