/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:54:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/01/14 18:00:37 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	if (src == NULL)
		return (NULL);
	while (src[len])
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (0);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}
