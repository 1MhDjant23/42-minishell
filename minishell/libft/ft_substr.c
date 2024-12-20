/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:25:39 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/13 18:25:00 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;
	size_t	size;

	if (!s)
		return (NULL);
	i = 0;
	size = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(start + s) < len)
		size = ft_strlen(s + start);
	else
		size = len;
	sub_str = malloc((size + 1) * sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	while (s[start] && (i < size) && (start < ft_strlen(s)))
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
