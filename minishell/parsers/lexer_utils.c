/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:13:42 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 12:21:25 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_just_send(t_list *list, char *str, t_token new_token, t_state *state)
{
	add_tail(list, new_elem(str, 1, new_token, *state));
	free(str);
	str = NULL;
}

void	token_state(char c, t_state *new_state, t_token *new_token)
{
	if (c == DOBL_Q)
	{
		*new_state = IN_DQUOTE;
		*new_token = DOBL_Q;
	}
	else
	{
		*new_state = IN_SIQUOTE;
		*new_token = SING_Q;
	}
}

void	handle_quotes(t_list *list, char *str, int *i, t_state *state)
{
	t_state	new_state;
	t_token	new_token;
	char	*aa;

	token_state(str[*i], &new_state, &new_token);
	if (*state == GENERAL)
	{
		_just_send(list, sub_str(str, *i, 1), new_token, state);
		*state = new_state;
	}
	else if (*state == new_state)
	{
		*state = GENERAL;
		_just_send(list, sub_str(str, *i, 1), new_token, state);
	}
	else
	{
		aa = sub_str(str, *i, 1);
		add_tail(list, new_elem(aa, 1, new_token, *state));
		free(aa);
		aa = NULL;
	}
}
