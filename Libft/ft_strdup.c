/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:57:39 by kakra             #+#    #+#             */
/*   Updated: 2024/06/12 10:23:25 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *str)
{
	int		i;
	int		j;
	char	*strr;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		i++;
	strr = (char *)malloc((i + 1) * sizeof(char));
	if (strr == NULL)
		return (0);
	while (str[j] != '\0')
	{
		strr[j] = str[j];
		j++;
	}
	strr[j] = '\0';
	return (strr);
}
