/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:06:30 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/03 02:37:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (size == 0 && (!src || !dest))
		return (0);
	while (dest[i] && i < size)
		i++;
	while (src[j] && size != 0 && i + j < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = 0;
	j = ft_strlen((char *)src);
	return (i + j);
}
