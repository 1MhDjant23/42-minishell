/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:06:49 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 11:35:45 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_check(t_minishel *data)
{
	char	*path;

	path = check_cmd_path(data, data->cmd->command);
	if (!path)
	{
		free_old_data(data);
		exit(data->exit_status);
	}
	return (path);
}

void	check_open_herd(t_minishel *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->herdoc)
		{
			unlink_files(cmd->hr_file);
			free_d_array(cmd->hr_file);
		}
		cmd = cmd->next;
	}
}

bool	save_prv_fd(t_command *cmd)
{
	if (check_if_builtins(cmd) == false)
		return (true);
	if (!cmd->redirect)
		return (true);
	cmd->prv_fd = malloc(sizeof(int));
	if (!cmd->prv_fd)
		return (false);
	return (true);
}

void	clean_after_signal(char **files)
{
	int	i;
	int	fd;

	i = 0;
	if (!files)
		return ;
	while (files[i])
	{
		fd = open(files[i], O_TRUNC, 0644);
		close(fd);
		i++;
	}
}

bool	check_name_file(t_command *cmd, int count, t_minishel *data)
{
	if (store_file_name(cmd, count) == false)
	{
		data->exit_status = 1;
		free_d_array(cmd->hr_file);
		return (false);
	}
	return (true);
}
