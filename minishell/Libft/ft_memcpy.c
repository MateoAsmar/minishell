/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:45:20 by kakra             #+#    #+#             */
/*   Updated: 2024/06/19 09:10:46 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destt;
	char	*srcc;
	size_t	i;

	if (!dest && !src)
		return (dest);
	i = 0;
	destt = (char *)dest;
	srcc = (char *)src;
	while (i < n)
	{
		destt[i] = srcc[i];
		i++;
	}
	return (destt);
}
