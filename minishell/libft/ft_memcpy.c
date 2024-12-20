/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:03:31 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/06 10:43:22 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
