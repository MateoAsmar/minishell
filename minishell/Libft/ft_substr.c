/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:24:03 by kakra             #+#    #+#             */
/*   Updated: 2024/06/12 13:14:20 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		slen;
	char				*memo;
	unsigned int		i;

	i = 0;
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (slen - start < len)
		len = slen - start;
	memo = (char *)malloc((len + 1) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	while (i < len)
	{
		memo[i] = s[start];
		start++;
		i++;
	}
	memo[i] = '\0';
	return (memo);
}
