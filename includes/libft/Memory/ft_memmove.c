/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:04:08 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/03 02:06:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, void *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src && size > 0)
	{
		size--;
		while (size)
		{
			((char *)dest)[size] = ((char *)src)[size];
			size--;
			if (size == 0)
				((char *)dest)[size] = ((char *)src)[size];
		}
	}
	else
	{
		while (i < size)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}
