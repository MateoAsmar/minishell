/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:28:01 by kakra             #+#    #+#             */
/*   Updated: 2024/11/16 18:23:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		f = i;
		j = 0;
		while (big[f] == little[j] && f < len)
		{
			f++;
			j++;
			if (little[j] == '\0' )
			{
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
