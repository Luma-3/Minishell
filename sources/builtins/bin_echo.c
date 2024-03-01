/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antgabri <antgabri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:10:35 by jbrousse          #+#    #+#             */
/*   Updated: 2024/03/01 11:57:30 by antgabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_builtins.h"

static int is_token(const char *start_token)
{
	if (ft_strncmp(start_token, "||", 2) == 0)
		return (true);
	if (ft_strncmp(start_token, "&&", 2) == 0)
		return (true);
	if (ft_strncmp(start_token, "|", 1) == 0)
		return (true);
	return (false);
}

static int skip_to_arg(const char *prompt, bool have_flag)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (have_flag == true && ft_strncmp(&prompt[i], "-n", 2) == 0)
		{
			i += 2;
			return (ft_skip_whitespaces(&prompt[i], i));
		}
		else if (have_flag == false && ft_strncmp(&prompt[i], "echo", 4) == 0)
		{
			i += 4;
			return (ft_skip_whitespaces(&prompt[i], i));
		}
		i++;
	}
	return (i);
}

static void	print_line(const char *str, t_list *envp)
{
	int		i;
	bool	is_between_quotes;
	char	quote_type;

	i = -1;
	is_between_quotes = false;
	while (str[i])
	{
		i++;
		if (is_token(&str[i]) == true && is_between_quotes == false)
			return ;
		if (str[i] == '$' && is_between_quotes == false)
		{
			i += handle_env(&str[i + 1], envp);
		}
		if (str[i] == '\\' && is_between_quotes == false)
			write(1, &str[++i], 1);
		else if (is_printable_quote(&str[i], &is_between_quotes, &quote_type) == true)
			write(1, &str[i], 1);
	}
}

int	ms_echo(const char *prompt, char **args, t_list **envp)
{
	bool	have_flag;
	int		i;
	
	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		have_flag = true;
	}
	i = skip_to_arg(prompt, have_flag);
	print_line(&prompt[i], *envp);
	if (have_flag == false)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
