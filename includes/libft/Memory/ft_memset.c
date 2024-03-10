/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:43:51 by edbernar          #+#    #+#             */
/*   Updated: 2023/10/30 17:04:24 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	unsigned int		i;
	char				*ptr;

	i = 0;
	ptr = (char *)pointer;
	while (i < count)
	{
		ptr[i] = value;
		i++;
	}
	return ((void *)ptr);
}
