/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:24:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/04 17:38:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline int	ft_pow(int nb, int exp)
{
	int	res;

	res = 1;
	while (--exp >= 0)
		res *= nb;
	return (res);
}

float	ft_atof(char *str)
{
	float	res;
	int		sign;
	int		dec_nb;

	res = 0;
	sign = 1;
	dec_nb = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
			dec_nb++;
		else
		{
			if (dec_nb == 0)
				res = res * 10 + (*str - '0');
			else
				res += ((float)(*str - '0') / ft_pow(10, dec_nb++));
		}
		str++;
	}
	return (res * sign);
}
