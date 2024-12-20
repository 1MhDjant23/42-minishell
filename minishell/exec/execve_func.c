/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:46:12 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 14:17:50 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(int i, int **pip)
{
	if (i > 0)
	{
		close(pip[i - 1][0]);
		close(pip[i - 1][1]);
	}
}

void	free_pipe(int **pipe, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(pipe[i]);
		pipe[i] = NULL;
		i++;
	}
	free(pipe);
	pipe = NULL;
}
