/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:22:39 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/14 21:40:23 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i + 1]);
		}
		i++;
	}
	if (s[i] != ch)
	{
		return (NULL);
	}
	return ((char *)&s[i]);
}
