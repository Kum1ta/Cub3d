/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:27:17 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/07 15:20:01 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *addr, int searchedChar, size_t size)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)addr;
	while (i < size)
	{
		if ((unsigned char)str[i] == (unsigned char)searchedChar)
			return (&str[i]);
		i++;
	}
	return (0);
}
