/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:58:52 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 23:46:14 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirections(char *str, int *i, t_list *list, t_state x)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		add_tail(list, new_elem("<<", 2, HERE_DOC, x));
		(*i)++;
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_tail(list, new_elem(">>", 2, APEND, x));
		(*i)++;
	}
	else if (str[*i] == '<')
	{
		add_tail(list, new_elem("<", 1, REDIR_IN, x));
	}
	else if (str[*i] == '>')
	{
		add_tail(list, new_elem(">", 1, REDIR_OUT, x));
	}
}

bool	keyword_hand(char c)
{
	if ((!(c >= '0' && c <= '9')) && (ft_isalpha(c) == false 
			&& c != '_' && c != '?'))
		return (false);
	return (true);
}

void	handle_env(char *str, int *i, t_list *list, t_state x)
{
	char	*sub;
	int		start;

	sub = NULL;
	if (str[*i] == ENV)
	{
		start = *i;
		(*i)++;
		while (str[*i] != ENV && str[*i] != '<' && str[*i] != '>' 
			&& str[*i] != '\0' && !is_operator(str[*i]) && str[*i] != PIPE_LINE
			&& keyword_hand(str[*i]) == true)
		{
			(*i)++;
		}
		sub = sub_str(str, start, *i - start);
		add_tail(list, new_elem(sub, str_len(sub), ENV, x));
		free(sub);
		(*i)--;
	}
}

void	handle_word(char *str, int *i, t_list *list, t_state x)
{
	char	*cpy;
	int		start;

	cpy = NULL;
	if (!is_operator(str[*i]) && str[*i] && str[*i] != '<' 
		&& str[*i] != '>' && str[*i] != ENV)
	{
		start = *i;
		while (str[*i] != ENV && str[*i] && !is_operator(str[*i]) 
			&& str[*i] != WHITE_SPACE && str[*i] != '<' && str[*i] != '>')
		{
			(*i)++;
		}
		cpy = sub_str(str, start, (*i - start));
		add_tail(list, new_elem(cpy, str_len(cpy), WORD, x));
		free(cpy);
		(*i)--;
	}
}

int	is_operator(char c)
{
	return (c == TAP || c == WHITE_SPACE || c == NEW_LINE 
		|| c == SING_Q || c == DOBL_Q || c == ESCAPE || c == PIPE_LINE);
}
