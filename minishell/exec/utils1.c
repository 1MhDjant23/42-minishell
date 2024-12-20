/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:30:37 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/13 22:36:23 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_minishel *data)
{
	data->command_line = NULL;
	data->path = NULL;
	data->cid = NULL;
	data->arg_counter = 0;
}

void	init_help(t_help *help)
{
	help->i = 0;
	help->store = NULL;
	help->tmp = NULL;
	help->value = NULL;
}

int	lenght(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->argument)
	{
		while (cmd->argument[i])
			i++;
	}
	if (cmd->command)
		i++;
	return (i + 1);
}

bool	special_char(char c)
{
	if (!ft_isalnum(c) && c != '_' && c != '=')
		return (true);
	return (false);
}

int	arg_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
