/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:20:47 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 13:26:52 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_exe_and_exist(char *command)
{
	if (!command)
		return (false);
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (true);
		else
			return (false);
	}
	else
		return (false);
	return (true);
}

bool	check_execute_file(char *cmd)
{
	if (access(cmd, F_OK) != 0 && cmd[0] == '/')
	{
		write(2, "minishell: No such file or directory\n", 37);
		exit(127);
	}
	return (true);
}

bool	just_simple_check(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (false);
	if (cmd[0] != '.' && cmd[1] != '/' && cmd[0] != '/')
		return (true);
	return (false);
}

void	print_not_found(t_minishel *data)
{
	write(2, "minishell: command not found\n", 29);
	data->exit_status = 127;
	exit(127);
}

char	*check_cmd_path(t_minishel *data, char *cmd)
{
	char	*c_path;
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	if (data->path && data->path[0])
	{
		while (data->path[++i] && just_simple_check(cmd) == true)
		{
			c_path = join_wit_path(data->path[i], cmd);
			if (check_exe_and_exist(c_path) == true)
				return (c_path);
			free(c_path);
		}
	}
	if (check_other_path(data, cmd))
		return (check_other_path(data, cmd));
	if (check_exe_and_exist(cmd) == true)
		return (cmd);
	if (check_execute_file(cmd) == true)
		return (free_old_data(data), print_not_found(data), NULL);
	return (NULL);
}
