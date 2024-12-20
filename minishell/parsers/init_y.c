/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_y.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:05:23 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/11 14:36:16 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*init_list(t_list *list)
{
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->end = NULL;
	list->size = 0;
	return (list);
}

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->next = NULL;
	return (redir);
}

t_herdoc	*init_herdoc(void)
{
	t_herdoc	*her;

	her = malloc(sizeof(t_herdoc));
	if (!her)
		return (NULL);
	her->delimiter = NULL;
	her->type = 100;
	her->exp = true;
	her->next = NULL;
	return (her);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->last_input = NON;
	cmd->command = NULL;
	cmd->out_exist = false;
	cmd->argument = NULL;
	cmd->redirect = NULL;
	cmd->herdoc = NULL;
	cmd->next = NULL;
	return (cmd);
}
