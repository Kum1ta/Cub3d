/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:56:10 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/07 14:14:05 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t elem_count, size_t elem_size)
{
	char			*str;

	if (!elem_count || !elem_count)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	if (elem_count * elem_size / elem_count != elem_size)
		return (NULL);
	str = malloc(elem_count * elem_size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, elem_count * elem_size);
	return ((void *)str);
}
