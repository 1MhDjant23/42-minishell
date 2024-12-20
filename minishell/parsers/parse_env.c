/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:41:22 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/14 23:21:15 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_err(t_elem **str, t_minishel *data)
{
	char	*sub;
	char	*hh;

	hh = NULL;
	sub = NULL;
	if ((*str)->content[1] == '?')
	{
		if (&(*str)->content[2] != NULL)
		{
			hh = ft_itoa(data->exit_status);
			sub = str_join(hh, &(*str)->content[2]);
			free(hh);
			free((*str)->content);
			(*str)->content = str_dup(sub);
			free(sub);
			(*str)->type = WORD;
			return ;
		}
		free((*str)->content);
		(*str)->content = str_dup(ft_itoa(data->exit_status));
	}
	(*str)->type = WORD;
}

void	env_hand(t_elem *str, t_minishel *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (str->content[1] == '?' || str->content[1] == '\0')
		{
			exit_err(&str, data);
			return ;
		}
		if (str_cmp(&str->content[1], tmp->name) == 0)
		{
			if (tmp->value != NULL)
			{
				free(str->content);
				str->content = str_dup(tmp->value);
				str->type = WORD;
				return ;
			}
		}
		tmp = tmp->next;
	}
	free(str->content);
	str->content = NULL;
	str->type = NON;
}
