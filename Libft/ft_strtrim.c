/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:17:30 by kakra             #+#    #+#             */
/*   Updated: 2024/06/19 08:32:27 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

int	check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	lenn(char const *set, char const *s1)
{
	int	len;
	int	start;
	int	end;

	len = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && check(s1[start], set))
	{
		start++;
	}
	while (end >= start && check(s1[end], set))
	{
		end--;
	}
	if (end >= start)
		len = end - start + 1;
	else
		len = 0;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lennn;
	char	*memo;
	int		pt;
	int		i;

	i = 0;
	pt = 0;
	lennn = lenn(set, s1);
	memo = (char *)malloc((lennn + 1) * sizeof(char));
	if (memo == NULL)
		return (NULL);
	while (s1[i] != '\0' && check(s1[i], set))
	{
		i++;
	}
	while (s1[i] != '\0' && pt < lennn)
	{
		memo[pt] = s1[i];
		pt++;
		i++;
	}
	memo[pt] = '\0';
	return (memo);
}

// int main ()
// {
// 	// ft_strtrim("Hello-a-world","---a");
// 	printf("%d",len("---a","Hello-a-world"));
// }