/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 06:58:17 by ysouhail          #+#    #+#             */
/*   Updated: 2024/12/12 18:01:24 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_cmp(char *s1, char *s2)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		x = s1[i] - s2[i];
		i++;
	}
	return (x);
}

bool	is_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

char	*sub_str(char *str, int start, int len)
{
	char	*sub;
	int		i;
	int		j;

	i = start;
	j = 0;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (j < len && str[i])
	{
		sub[j] = str[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*str_dup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	if (!str)
	{
		return (NULL);
	}
	dup = malloc(str_len(str)+1);
	if (!dup)
	{
		return (NULL);
	}
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
