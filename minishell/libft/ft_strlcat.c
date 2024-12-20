/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:51:50 by mait-taj          #+#    #+#             */
/*   Updated: 2024/12/12 13:29:50 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_s;
	size_t	len_d;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (len_d >= dstsize)
		len_d = dstsize;
	if (len_d == dstsize)
		return (len_s + dstsize);
	if (len_s < dstsize - len_d)
	{
		ft_memcpy(dst + len_d, src, len_s + 1);
	}
	else
	{
		ft_memcpy(dst + len_d, src, dstsize - len_d - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len_d + len_s);
}
