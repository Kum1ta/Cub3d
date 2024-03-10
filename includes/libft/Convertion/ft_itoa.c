/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:02:42 by edbernar          #+#    #+#             */
/*   Updated: 2024/01/19 13:28:25 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	nbr_len(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static int	define_sign(int *n)
{
	if (*n < 0)
	{
		*n = -*n;
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	len = nbr_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len--] = 0;
	sign = define_sign(&n);
	while (len >= 0)
	{
		if (len == 0 && sign)
			str[0] = '-';
		else
			str[len] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (str);
}
