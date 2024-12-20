/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:51:38 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 14:55:29 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_str(char *str, int fd)
{
	write(fd, str, str_len(str));
}

t_stax	*init_stax(void)
{
	t_stax	*yssf;

	yssf = malloc(sizeof(t_stax));
	yssf->count = 0;
	yssf->x = 0;
	yssf->pip = 0;
	yssf->redir = 0;
	return (yssf);
}

bool	syntax_red(t_elem *next)
{
	if ((next && (next->type == PIPE_LINE || 
				(next->state == GENERAL && is_redir(next) == true))))
	{
		return (false);
	}
	return (true);
}

void	sysntax_error(t_list *list, t_minishel *data)
{
	t_elem	*next;
	t_elem	*current;

	next = NULL;
	current = list->head;
	data->yssf = init_stax();
	while (current != NULL)
	{
		if (is_redir(current) == true && current->state == GENERAL)
		{
			next = skip_space(current->next);
			if (current->next == NULL || !redir_syntax(current) 
				|| syntax_red(next) == false)
			{
				data->yssf->redir = 1;
				break ;
			}
		}
		check_quotes(current, &data->yssf->count, &data->yssf->x);
		if (current->content[0] == PIPE_LINE)
			data->yssf->pip = check_pipe(list, current);
		current = current->next;
	}
	handle_syntax_error(list, data);
	free(data->yssf);
}
