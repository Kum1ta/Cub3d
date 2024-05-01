/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:59:39 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/07 13:30:34 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned int	i;
	unsigned char	*new_dest;
	unsigned char	*new_src;

	i = 0;
	if ((!src && !dest))
		return (NULL);
	new_dest = (unsigned char *)dest;
	new_src = (unsigned char *)src;
	while (i < size)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	return ((void *)new_dest);
}
