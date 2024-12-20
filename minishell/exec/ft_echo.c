/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:03:59 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 14:02:04 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_option(char *opt)
{
	int		i;

	i = 0;
	if (opt[i] && opt[i] == '-')
		i++;
	else
		return (false);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	print_arg(char *arg)
{
	if (!arg)
		return ;
	write(STDOUT_FILENO, arg, ft_strlen(arg));
}

void	built_echo(t_command *cmd)
{
	int			i;
	bool		nl;

	nl = false;
	i = 0;
	if (cmd->argument && cmd->argument[0])
	{
		while (cmd->argument[i] && check_option(cmd->argument[i]) == true)
		{
			nl = true;
			i++;
		}
		while (cmd->argument[i])
		{
			print_arg(cmd->argument[i]);
			if (cmd->argument[i + 1])
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
		if (nl == false)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
