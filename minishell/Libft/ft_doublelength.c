/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublelength.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:22:53 by kakra             #+#    #+#             */
/*   Updated: 2024/08/24 21:12:06 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_doublelength(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
