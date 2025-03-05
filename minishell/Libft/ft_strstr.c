/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:55 by kakra             #+#    #+#             */
/*   Updated: 2024/11/15 21:22:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*h_tmp;
	const char	*n_tmp;

	if (*needle == '\0')
		return ((char *)haystack);
	h = haystack;
	while (*h != '\0')
	{
		h_tmp = h;
		n_tmp = needle;
		while (*n_tmp != '\0' && *h_tmp == *n_tmp)
		{
			h_tmp++;
			n_tmp++;
		}
		if (*n_tmp == '\0')
			return ((char *)h);
		h++;
	}
	return (NULL);
}
