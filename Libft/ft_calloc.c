/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:28:11 by kakra             #+#    #+#             */
/*   Updated: 2024/06/19 08:30:53 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	void	*memo;

	if ((nelem != 0 && size != 0) && (nelem * size) / size != nelem)
		return (NULL);
	memo = (void *)malloc(nelem * size);
	if (memo == NULL)
		return (NULL);
	ft_bzero(memo, nelem * size);
	return (memo);
}
