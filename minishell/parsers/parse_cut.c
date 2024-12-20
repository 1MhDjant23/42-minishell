/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:51:48 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/14 23:23:09 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (str_dup(s2));
	str = malloc(str_len(s1) + str_len(s2) +1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

bool	ft_chcker(t_elem *list)
{
	if ((list->type == WHITE_SPACE || list->type == ENV || list->type == SING_Q 
			|| list->type == DOBL_Q 
			|| list->type == TAP) && list->state == GENERAL)
	{
		return (false);
	}
	else if ((list->type == ENV && list->state == IN_DQUOTE)
		|| list->type == NON)
	{
		return (false);
	}
	return (true);
}

bool	_breaker(t_elem *str)
{
	if ((str->type == WHITE_SPACE || str->type == TAP) && str->state == GENERAL)
	{
		return (true);
	}
	if ((str->type == PIPE_LINE || is_redir(str)) && str->state == GENERAL)
	{
		return (true);
	}
	return (false);
}

char	*hand_cuting(char *rs, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = str_join(rs, str);
	free(rs);
	rs = str_dup(tmp);
	free(tmp);
	tmp = NULL;
	return (rs);
}

char	*cut_string(t_elem **list, t_minishel *data)
{
	char	*rs;
	bool	x;

	x = false;
	rs = NULL;
	while ((*list))
	{
		if (!(*list) || _breaker(*list) == true)
			break ;
		if (((*list)->type == ENV) && ((*list)->state == GENERAL 
				|| (*list)->state == IN_DQUOTE))
			env_hand((*list), data);
		if (!(*list))
			break ;
		if (ft_chcker(*list) == true)
			rs = hand_cuting(rs, (*list)->content);
		if ((*list)->type != NON)
			x = true;
		(*list) = (*list)->next;
	}
	if (rs == NULL && x == true)
		rs = str_dup("");
	return (rs);
}
