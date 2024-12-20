/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:34:57 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/14 23:23:59 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	simple_cmd(t_flags *x, t_elem **str, t_minishel *data, t_command **cmd)
{
	if ((*str)->type == PIPE_LINE)
		return ;
	x->sub = cut_string(str, data);
	if (x->com == false && x->sub)
	{
		(*cmd)->command = str_dup(x->sub);
		x->com = true;
	}
	else
		arg_fuller(x->sub, (*cmd));
	free(x->sub);
	x->sub = NULL;
}

void	handle_redirection(t_elem **str, t_command *current, t_minishel *data)
{
	t_redir	*redir;

	redir = init_redir();
	redir->type = (*str)->type;
	*str = (*str)->next;
	while ((*str)->type == WHITE_SPACE)
	{
		*str = (*str)->next;
	}
	redir->file = cut_string(str, data);
	add_redir(&current->redirect, redir);
}

void	init_flag(t_flags *flag)
{
	flag->com = false;
	flag->sp = false;
	flag->sub = NULL;
}

bool	struct_u(t_elem **str, t_command **cmd, t_minishel *data, t_flags *x)
{
	t_herdoc	*new_herdoc;

	if (is_redir(*str) == true && (*str)->state == GENERAL)
	{
		if ((*str)->type == HERE_DOC)
		{
			new_herdoc = init_herdoc();
			new_herdoc->type = (*str)->type;
			(*str) = (*str)->next;
			while ((*str) && (*str)->type == WHITE_SPACE)
				(*str) = (*str)->next;
			new_herdoc->delimiter = cut_herdoc(str, new_herdoc);
			add_herdoc(&(*cmd)->herdoc, new_herdoc);
		}
		else
			handle_redirection(&(*str), *cmd, data);
	}
	(*str) = skip_space((*str));
	if ((*str) && is_redir((*str)) == false)
		simple_cmd(x, &(*str), data, cmd);
	if (!(*str) || ((*str)->type == PIPE_LINE && (*str)->state == GENERAL))
		return (false);
	return (true);
}

void	struct_full(t_list *list, t_minishel *data)
{
	t_elem		*str;
	t_flags		flags;
	t_command	*current;

	data->cmd = NULL;
	current = NULL;
	str = list->head;
	while (str != NULL)
	{
		current = init_command();
		init_flag(&flags);
		check_last_redir(str, current);
		while (str != NULL)
		{
			if (struct_u(&str, &current, data, &flags) == false)
				break ;
		}
		if (str != NULL && str->type == PIPE_LINE && str->state == GENERAL)
			str = str->next;
		add_back(&data->cmd, current);
	}
	execute(&data);
	free_things(&list, &data->cmd);
}
