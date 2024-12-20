/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 00:45:29 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/07 14:10:29 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*tmp;
	char			ch;

	i = 0;
	tmp = NULL;
	ch = (char) c;
	while (s[i])
	{
		if (s[i] == ch)
		{
			tmp = (char *)&s[i];
		}
		i++;
	}
	if (s[i] == '\0' && ch == '\0')
	{
		return ((char *) &s[i]);
	}
	return (tmp);
}
