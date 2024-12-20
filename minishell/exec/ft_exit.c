/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:42:25 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 14:01:26 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	interpret_arg(t_minishel *data, char **arg)
{
	int	i;

	i = 0;
	if (arg[0][0] == '+' || arg[0][0] == '-')
		i++;
	while (arg[0][i])
	{
		if (ft_isdigit(arg[0][i]) == false)
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			data->exit_status = 255;
			return (false);
		}
		i++;
	}
	if (arg_count(arg) > 1)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		data->exit_status = 1;
		return (false);
	}
	return (true);
}

void	built_exit(t_minishel *data, t_command *cmd)
{
	int	status;

	if (!cmd->argument || cmd->argument[0] == NULL)
		exit(data->exit_status);
	if ((cmd->argument[0][0] == '+' || cmd->argument[0][0] == '-')
		&& (cmd->argument[0][1] == '+' || cmd->argument[0][1] == '-'))
	{
		write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
		data->exit_status = 255;
		exit(255);
	}
	if (interpret_arg(data, cmd->argument) == false)
	{
		if (data->exit_status == 255)
			exit(255);
		return ;
	}
	status = ft_atoi(cmd->argument[0]);
	if (status < 0)
		status += 256;
	write(STDERR_FILENO, "exit\n", 5);
	exit(status);
}
