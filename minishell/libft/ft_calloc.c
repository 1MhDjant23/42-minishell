/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:20:56 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/13 19:06:36 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp_calloc;

	if (count > 2147483648 && size > 2147483648)
		return (NULL);
	tmp_calloc = malloc(count * size);
	if (!tmp_calloc)
		return (NULL);
	ft_memset(tmp_calloc, 0, count * size);
	return (tmp_calloc);
}
