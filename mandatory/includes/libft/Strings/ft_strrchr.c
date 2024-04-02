/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/01/12 22:05:56 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (unsigned char)chr)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}
