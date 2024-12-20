/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:42:26 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 17:40:54 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes(t_elem *current, int *count, int *x)
{
	if (current->type == SING_Q && current->state == GENERAL)
	{
		(*count)++;
	}
	else if (current->type == DOBL_Q && current->state == GENERAL)
	{
		(*x)++;
	}
}

int	check_pipe(t_list *list, t_elem *current)
{
	int		i;
	t_elem	*space;

	i = 0;
	space = NULL;
	if ((current->next && current->next->type == PIPE_LINE 
			&& current->state == GENERAL) || 
		(list->head->content[i] == PIPE_LINE) || list->end->type == PIPE_LINE)
	{
		return (1);
	}
	if (list->head->type == WHITE_SPACE && list->head->state == GENERAL)
	{
		space = skip_space(list->head);
		if (space->type == PIPE_LINE)
			return (1);
	}
	return (0);
}

void	handle_syntax_error(t_list *list, t_minishel *data)
{
	if (data->yssf->count % 2 != 0 || data->yssf->x % 2 != 0)
	{
		put_str("syntax error: unexpected EOF\n", 2);
		data->exit_status = 258;
		free_things(&list, NULL);
	}
	else if (data->yssf->pip == 1)
	{
		put_str("syntax error near unexpected token `|`\n", 2);
		data->exit_status = 258;
		free_things(&list, NULL);
	}
	else if (data->yssf->redir == 1)
	{
		put_str("minishell: syntax error redirection\n", 2);
		data->exit_status = 258;
		free_things(&list, NULL);
	}
	else
		struct_full(list, data);
}

t_elem	*skip_space(t_elem *str)
{
	if (!str)
	{
		return (NULL);
	}
	while (str)
	{
		while (str->type == WHITE_SPACE || str->type == TAP)
		{
			str = str->next;
			if (!str)
			{
				break ;
			}
		}
		break ;
	}
	return (str);
}

bool	redir_syntax(t_elem *str)
{
	t_elem	*next;

	next = skip_space(str->next);
	if (!next || ((next->type != WORD && next->type != ENV 
				&& next->state != GENERAL)))
		return (false);
	return (true);
}
