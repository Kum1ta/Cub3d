/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:52:50 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/03 02:42:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	if (size == 0 && !str)
		return (0);
	if (!to_find[0])
		return ((char *)str);
	while (str[++i] && i < size)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] && i + j < size)
			j++;
		if (!to_find[j])
			return ((char *)&str[i]);
	}
	return (0);
}
