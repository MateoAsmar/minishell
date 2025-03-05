/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:43:32 by kakra             #+#    #+#             */
/*   Updated: 2024/06/12 12:35:53 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strrchr(char *str, int c)
{
	int		i;
	int		j;
	char	cc;

	cc = c;
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
		{
			j = 1;
			while (str[i + j] != cc && str[i + j])
			{
				j++;
			}
			if (str[i + j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}
