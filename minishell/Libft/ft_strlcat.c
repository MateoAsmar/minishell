/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakra <kakra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:58:47 by kakra             #+#    #+#             */
/*   Updated: 2024/06/11 13:19:57 by kakra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size)
{
	int				srclen;
	unsigned int	destlen;
	unsigned int	i;

	i = 0;
	srclen = 0;
	destlen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (dst[destlen] != '\0')
		destlen++;
	if (size == 0 || destlen >= size)
		return (size + srclen);
	while (src[i] != '\0' && i < size - destlen - 1)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
