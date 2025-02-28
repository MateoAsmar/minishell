/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:21:07 by kakra             #+#    #+#             */
/*   Updated: 2024/04/25 13:49:49 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	s1size(char *s1)
{
	int		len1;

	len1 = 0;
	while (*s1 != '\0')
	{
		len1++;
		s1++;
	}
	return (len1);
}

int	s2size(char *s2)
{
	int		len2;

	len2 = 0;
	while (*s2 != '\0')
	{
		len2++;
		s2++;
	}
	return (len2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] != s2[i])
		{
			if (s1size(s1) > s2size(s2))
				return (s1[i] - s2[i]);
			else
				return (s1[i] - s2[i]);
		}
	}
	if (s1size(s1) > s2size(s2))
		return (s1[i] - s2[i]);
	else
		return (s1[i] - s2[i]);
	return (0);
}
