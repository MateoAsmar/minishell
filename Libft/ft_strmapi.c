/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:22:43 by kakra             #+#    #+#             */
/*   Updated: 2024/06/17 11:36:49 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*memo;

	i = 0;
	memo = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		memo[i] = f(i, s[i]);
		i++;
	}
	memo[i] = '\0';
	return (memo);
}
