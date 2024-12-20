/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:26:04 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/09 21:43:44 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handl_error(const char *err_mess, int ex_st, t_minishel *data)
{
	if (err_mess)
		perror(err_mess);
	data->exit_status = ex_st;
	return ;
}
