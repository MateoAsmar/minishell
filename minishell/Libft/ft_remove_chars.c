/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:59:41 by kakra             #+#    #+#             */
/*   Updated: 2024/09/01 18:51:53 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_chars(char *str, const char *remove)
{
	int	src;
	int	dest;
	int	remove_flags[256];

	ft_memset(remove_flags, 0, sizeof(remove_flags));
	src = 0;
	dest = 0;
	while (remove[src])
	{
		remove_flags[(unsigned char)remove[src]] = 1;
		src++;
	}
	src = 0;
	while (str[src])
	{
		if (!remove_flags[(unsigned char)str[src]])
		{
			str[dest++] = str[src];
		}
		src++;
	}
	str[dest] = '\0';
}
