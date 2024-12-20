/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:08:20 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 11:44:58 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**return_pipe(t_minishel *data, int x)
{
	int	**pip; 
	int	i;

	if (x >= 1392)
		return (NULL);
	pip = (int **)malloc(sizeof(int *) * x);
	if (!pip)
	{
		perror("malloc");
		free_old_data(data);
		data->exit_status = 1;
		return (NULL);
	}
	i = 0;
	while (i < x)
	{
		pip[i] = (int *)malloc(sizeof(int ) * 2);
		if (!pip[i])
			exit(EXIT_FAILURE);
		i++;
	}
	return (pip);
}

void	synch_pipe(int **pip, int indx, int n_cmd, t_command *cmd)
{
	if (indx > 0)
	{
		if (cmd->last_input != HERE_DOC && cmd->last_input != REDIR_IN)
			dup2(pip[indx - 1][0], STDIN_FILENO);
		close(pip[indx - 1][0]);
		close(pip[indx - 1][1]);
	}
	if (indx < n_cmd - 1)
	{
		if (cmd->out_exist == false)
			dup2(pip[indx][1], STDOUT_FILENO);
		close(pip[indx][1]);
		close(pip[indx][0]);
	}
}
