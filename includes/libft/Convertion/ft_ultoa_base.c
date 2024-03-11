/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:53:55 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:44:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_ultoabase_len(unsigned long nb, const char *base)
{
	size_t				len;
	size_t				baselen;

	baselen = ft_strlen((char *) base);
	if (baselen <= 0)
		return (0);
	if (nb == 0)
		return (1);
	len = 0;
	while (nb > 0)
	{
		nb /= baselen;
		len++;
	}
	return (len);
}

static void	ft_ultoab_fill(unsigned long nb, char *base, char *res, size_t len)
{
	size_t				baselen;

	baselen = ft_strlen(base);
	while (nb > baselen - 1)
	{
		res[--len] = base[nb % baselen];
		nb /= baselen;
	}
	res[len - 1] = base[nb % baselen];
}

char	*ft_ultoa_base(unsigned long nb, const char *base)
{
	char	*res;
	size_t	len;

	len = ft_ultoabase_len(nb, base);
	if (len == 0)
		return (NULL);
	res = malloc((len + 1) * sizeof(char));
	res[len] = 0;
	if (res == NULL)
		return (NULL);
	ft_ultoab_fill(nb, (char *) base, res, len);
	return (res);
}
