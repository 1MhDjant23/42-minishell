/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-taj <mait-taj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:12:30 by mait-taj          #+#    #+#             */
/*   Updated: 2024/01/04 18:21:16 by mait-taj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_int(long n)
{
	int	i;

	i = 0;
	if (n > 0)
	{
		while (n != 0)
		{
			i++;
			n /= 10;
		}
	}
	else
	{
		n = -n;
		while (n != 0)
		{
			i++;
			n /= 10;
		}
		i += 1;
	}
	return (i);
}

static char	*i_is_zero(int n)
{
	char	*result;

	result = malloc(2);
	if (result == NULL)
		return (NULL);
	result[n] = '0';
	result[n + 1] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*i_to_s;
	long	i_n;

	len = len_int(n);
	i_n = 0;
	if (n == 0)
		return (i_is_zero(n));
	i_to_s = (char *)malloc((len + 1) * sizeof(char));
	if (i_to_s == NULL)
		return (NULL);
	i_n = n;
	if (i_n < 0)
	{
		i_to_s[0] = '-';
		i_n = -i_n;
	}
	i_to_s[len] = '\0';
	while ((len > 0) && (i_n != 0))
	{
		len--;
		i_to_s[len] = '0' + (i_n % 10);
		i_n /= 10;
	}
	return (i_to_s);
}
