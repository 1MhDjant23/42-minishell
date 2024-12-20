/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:57:58 by mait-taj          #+#    #+#             */
/*   Updated: 2023/12/25 22:05:00 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				len;
	char			*c_mapi;

	len = ft_strlen(s);
	c_mapi = (char *)malloc((len + 1) * sizeof(char));
	if (c_mapi == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		c_mapi[i] = (*f)(i, s[i]);
		i++;
	}
	c_mapi[i] = '\0';
	return (c_mapi);
}
