/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addstring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:24:28 by kakra             #+#    #+#             */
/*   Updated: 2024/11/15 21:18:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**add_string_to_array(char **array, int size, const char *new_string)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc((size + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (i < size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = malloc(ft_strlen(new_string) + 1);
	if (!new_array[i])
		return (NULL);
	ft_strcpy(new_array[i], (char *)new_string);
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}
