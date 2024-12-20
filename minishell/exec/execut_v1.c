/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:53:28 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 13:23:56 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_v2(t_minishel *data, char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/' && cmd[2] != '\0')
	{
		if (access(&cmd[2], F_OK) != 0)
		{
			free_old_data(data);
			write(2, "minishell: No such file or directory\n", 37);
			exit(127);
		}
		if (access(&cmd[2], F_OK) == 0)
		{
			if (access(&cmd[2], X_OK) != 0)
			{
				free_old_data(data);
				write(2, "minishell: Permission denied\n", 29);
				exit(126);
			}
			else
				return (cmd);
		}
	}
	return (NULL);
}

char	*print_err(void)
{
	write(2, "minishell: .: filename argument required\n", 41);
	write(2, ".: usage: . filename [arguments]\n", 33);
	exit(2);
}

void	exiting_now(t_minishel *data)
{
	free_old_data(data);
	write(2, "minishell: Permission denied\n", 29);
	exit(126);
}

char	*check_other_path(t_minishel *data, char *path)
{
	struct stat	path_stat;

	if (path[0] == '.' && path[1] == '\0')
		return (free_old_data(data), print_err(), NULL);
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		free_old_data(data);
		return (write(2, "minishell: is a directory\n", 26), exit(126), NULL);
	}
	if (check_v2(data, path))
		return (check_v2(data, path));
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			data->exit_status = 0;
			return (path);
		}
		else
			exiting_now(data);
	}
	return (NULL);
}

bool	malloc_cid_err(t_minishel *data, int size, t_type stat, char *err)
{
	if (stat == alloc)
	{
		data->cid = malloc(sizeof(int) * size);
		if (!data->cid)
		{
			data->exit_status = 1;
			free_old_data(data);
			return (false);
		}
	}
	if (stat == error)
	{
		perror(err);
		data->exit_status = 1;
		free_old_data(data);
		return (false);
	}
	return (true);
}
