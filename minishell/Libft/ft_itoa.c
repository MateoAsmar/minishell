/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:27:43 by kakra             #+#    #+#             */
/*   Updated: 2024/06/17 15:15:55 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	len(long n, int *sign)
{
	int	lenn;

	lenn = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		*sign = -1;
		n = n * -1;
		lenn++;
	}
	while (n != 0)
	{
		lenn++;
		n = n / 10;
	}
	return (lenn);
}

long	ft_abs(long f)
{
	if (f < 0)
		return (-1 * f);
	return (f);
}

char	*ft_itoa(int n)
{
	long	f;
	long	len1;
	char	*ptr;
	int		sign;

	f = n;
	sign = 1;
	len1 = len(f, &sign);
	ptr = malloc(sizeof(char) * (len1 + 1));
	if (!ptr)
		return (NULL);
	ptr[len1] = '\0';
	len1--;
	f = ft_abs(f);
	while (len1 >= 0)
	{
		ptr[len1] = f % 10 + '0';
		f /= 10;
		len1--;
	}
	if (sign == -1)
		ptr[0] = '-';
	return (ptr);
}
