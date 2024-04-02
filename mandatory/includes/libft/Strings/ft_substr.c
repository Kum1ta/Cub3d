/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:10:55 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/07 15:03:25 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	int				total_len;
	char			*str;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s) <= len)
		total_len = ft_strlen(s) - start + 1;
	else
		total_len = len + 1;
	str = malloc(total_len * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < len && s[i + start])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
