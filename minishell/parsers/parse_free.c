/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:02:26 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 23:35:03 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_herdoc_redir(t_command *cmd)
{
	t_redir		*next_red;
	t_herdoc	*next_herd;

	while (cmd->redirect)
	{
		next_red = cmd->redirect->next;
		free(cmd->redirect->file);
		cmd->redirect->file = NULL;
		free(cmd->redirect);
		cmd->redirect = next_red;
	}
	while (cmd->herdoc)
	{
		next_herd = cmd->herdoc->next;
		free(cmd->herdoc->delimiter);
		cmd->herdoc->delimiter = NULL;
		free(cmd->herdoc);
		cmd->herdoc = next_herd;
	}
}

void	free_comand(t_command *cmd)
{
	t_command		*tmp;
	int				i;

	while (cmd)
	{
		i = 0;
		tmp = cmd->next;
		free(cmd->command);
		cmd->command = NULL;
		free_herdoc_redir(cmd);
		if (cmd->argument)
		{
			while (cmd->argument[i])
			{
				free(cmd->argument[i]);
				cmd->argument[i] = NULL;
				i++;
			}
			free(cmd->argument);
			cmd->argument = NULL;
		}
		free(cmd);
		cmd = tmp;
	}
}

void	free_list(t_list *list)
{
	t_elem	*current;
	t_elem	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(list);
}

void	free_things(t_list **list, t_command **current)
{
	if (list && *list)
	{
		free_list(*list);
		*list = NULL;
	}
	if (current && *current)
	{
		free_comand(*current);
		*current = NULL;
	}
}
