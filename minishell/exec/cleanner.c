/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:50:46 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/15 15:03:36 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_d_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	unlink_files(char **files)
{
	int	i;

	i = 0;
	if (files && files[0])
	{
		while (files[i])
		{
			if (access(files[i], F_OK) == 0)
			{
				if (unlink(files[i]) == -1)
				{
					perror("unlink");
					exit(EXIT_FAILURE);
				}
			}
			i++;
		}
	}
}

void	free_old_data(t_minishel *data)
{
	if (data->cid)
	{
		free(data->cid);
		data->cid = NULL;
	}
	if (data->command_line && data->command_line[0])
	{
		free_d_array((data->command_line));
	}
	if (data->path)
	{
		free_d_array(data->path);
		data->path = NULL;
	}
}

void	cleann_exec(t_minishel *data, t_command *cmd, t_type s1, t_type s2)
{
	if (cmd->redirect && s1 == built)
	{
		dup2(cmd->prv_fd[0], STDOUT_FILENO);
		close(cmd->prv_fd[0]);
		free(cmd->prv_fd);
		cmd->prv_fd = NULL;
	}
	if (s2 == clean)
	{
		free_old_data(data);
	}
	if (s1 == error)
		exit(EXIT_FAILURE);
	return ;
}
