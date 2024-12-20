/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:38:19 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 18:06:36 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir(t_redir **list, t_redir *new)
{
	t_redir	*last;

	last = *list;
	if (!(*list) && !new)
		return ;
	if (!list || !(*list)) 
	{
		*list = new;
	}
	else 
	{
		while ((last)->next != NULL)
		{
			(last) = (last)->next;
		}
		last->next = new;
	}
}

void	add_herdoc(t_herdoc **list, t_herdoc *new)
{
	t_herdoc	*last;

	last = *list;
	if (!(*list) && !new)
		return ;
	if (!list || !(*list)) 
	{
		*list = new;
	}
	else 
	{
		while ((last)->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
}

void	add_back(t_command **list, t_command *new)
{
	t_command	*last;

	last = *list;
	if (!(*list) && !new)
		return ;
	if (!list || !(*list)) 
	{
		*list = new;
	}
	else 
	{
		while ((last)->next != NULL)
		{
			(last) = (last)->next;
		}
		last->next = new;
	}
}
