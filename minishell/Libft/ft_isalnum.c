/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:32:59 by kakra             #+#    #+#             */
/*   Updated: 2024/06/10 13:42:59 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int arg)
{
	if ((arg >= '0' && arg <= '9')
		|| (arg >= 'a' && arg <= 'z')
		|| (arg >= 'A' && arg <= 'Z'))
	{
		return (1);
	}
	return (0);
}
