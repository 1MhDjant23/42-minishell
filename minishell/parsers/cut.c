/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:58:46 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 23:37:31 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	hrdoc_checker(t_elem *list)
{
	if ((list->type == SING_Q || list->type == DOBL_Q) 
		&& list->state == GENERAL)
		return (false);
	return (true);
}

char	*cut_herdoc(t_elem **list, t_herdoc *hero)
{
	char	*rs;
	char	*tmp;

	rs = NULL;
	tmp = NULL;
	while ((*list))
	{
		if (((*list)->type == ' ' || is_redir(*list) || (*list)->type == TAP
				|| (*list)->type == PIPE_LINE) && (*list)->state == GENERAL)
			break ;
		if (((*list)->type == SING_Q || (*list)->type == DOBL_Q))
			hero->exp = false;
		if (hrdoc_checker(*list) == true)
		{
			tmp = str_join(rs, (*list)->content);
			free(rs);
			rs = str_dup(tmp);
			free(tmp);
			tmp = NULL;
		}
		(*list) = (*list)->next;
	}
	if (rs == NULL)
		rs = str_dup("");
	return (rs);
}
