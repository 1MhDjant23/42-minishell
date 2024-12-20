/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:08:06 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 19:26:22 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_cd(t_minishel *data, t_command *cmd)
{
	char		*dir;

	update_working_dir(OLD, data);
	if (!cmd->argument || cmd->argument[0][0] == '~')
	{
		dir = get_env(data, "HOME");
		if (dir == NULL)
		{
			data->exit_status = 1;
			return ((void)write(2, "minishell: cd: HOME not set\n", 28));
		}
	}
	else
		dir = ft_strdup(cmd->argument[0]);
	if (chdir(dir) != 0)
	{
		data->exit_status = 1;
		free(dir);
		perror("minishell");
		return ;
	}
	free(dir);
	dir = NULL;
	update_working_dir(PWD, data);
	data->exit_status = 0;
}
