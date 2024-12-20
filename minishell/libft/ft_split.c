/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:57:35 by mait-taj          #+#    #+#             */
/*   Updated: 2024/11/03 12:15:03 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char ch)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (str[j])
	{
		if (str[j] == ch)
			j++;
		else
		{
			count++;
			while (str[j] != '\0' && str[j] != ch)
				j++;
		}
	}
	return (count);
}

static void	ft_free(char **res_split)
{
	int	i;

	i = 0;
	while (res_split[i] != NULL)
	{
		free(res_split[i]);
		i++;
	}
	free(res_split);
}

static char	**fill_case(char **res_split, const char *s, char c, int c_words)
{
	int		i;
	int		ac;
	int		start;
	char	*swp;

	i = 0;
	ac = 0;
	while (s[i] && ac < c_words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		swp = ft_substr(s, start, i - start);
		if (!swp)
		{
			res_split[ac] = NULL;
			ft_free(res_split);
			return (NULL);
		}
		res_split[ac++] = swp;
	}
	res_split[ac] = NULL;
	return (res_split);
}

char	**ft_split(char const *s, char c)
{
	char	**resultats;
	int		c_wor;

	if (!s)
		return (NULL);
	c_wor = count_words(s, c);
	resultats = (char **)malloc((c_wor + 1) * sizeof(char *));
	if (resultats == NULL)
		return (NULL);
	resultats = fill_case(resultats, s, c, c_wor);
	if (!resultats)
		return (NULL);
	return (resultats);
}
