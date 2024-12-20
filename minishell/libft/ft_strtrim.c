/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:31:31 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/13 18:22:25 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*after_trim;
	size_t	j;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	if (s1[i] == '\0')
	{
		return (ft_strdup(""));
	}
	while (ft_strrchr(set, s1[i]))
	{
		i++;
	}
	while (ft_strrchr(set, s1[j]))
	{
		j--;
	}
	after_trim = ft_substr(s1, i, j - i + 1);
	if (after_trim == NULL)
		return (NULL);
	return (after_trim);
}
