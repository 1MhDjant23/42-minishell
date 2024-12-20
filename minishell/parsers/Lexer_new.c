/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:59:19 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 09:57:04 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty(t_list *list)
{
	return (list->head == NULL);
}

t_elem	*new_elem(char *content, int len, t_token type, t_state state)
{
	t_elem	*newnode;

	newnode = malloc(sizeof(t_elem));
	if (!newnode)
		return (NULL);
	newnode->content = str_dup(content);
	newnode->len = len;
	newnode->type = type; 
	newnode->state = state;
	newnode->next = NULL;
	return (newnode);
}

void	add_tail(t_list *list, t_elem *new)
{
	if (is_empty(list)) 
	{
		list->head = new;
		list->end = new;
	}
	else 
	{
		list->end->next = new;
		list->end = new;
	}
	list->size++;
}

t_list	*ft_lexer(char *str)
{
	t_list	*list;
	t_state	state;
	int		i;

	list = NULL;
	list = init_list(list);
	state = GENERAL;
	i = 0;
	while (str[i])
	{
		if (str[i] == SING_Q || str[i] == DOBL_Q)
			handle_quotes(list, str, &i, &state);
		else if (is_operator(str[i]))
		{
			_just_send(list, sub_str(str, i, 1), str[i], &state);
		}
		else
		{
			handle_word(str, &i, list, state);
			handle_env(str, &i, list, state);
			handle_redirections(str, &i, list, state);
		}
		i++;
	}
	return (list);
}
