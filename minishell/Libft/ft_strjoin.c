/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:15:47 by kakra             #+#    #+#             */
/*   Updated: 2024/06/12 12:36:24 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*memo;
	int		j;

	j = 0;
	i = 0;
	memo = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	while (j < ft_strlen(s1))
	{
		memo[i++] = s1[j];
		j++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		memo[i] = s2[j];
		i++;
		j++;
	}
	memo[i] = '\0';
	return (memo);
}
