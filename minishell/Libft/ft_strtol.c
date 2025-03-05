/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:03:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/15 21:03:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static long	ft_process_number(const char *str, int *i, long sign, int *error)
{
	long	result;

	result = 0;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		if ((result > (LONG_MAX / 10)) || (result == (LONG_MAX / 10)
				&& (str[*i] - '0') > (LONG_MAX % 10)))
		{
			*error = 1;
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

long	ft_strtol(const char *str, int *error)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	*error = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ft_process_number(str, &i, sign, error);
	if (str[i] != '\0')
		*error = 1;
	return (result * sign);
}
