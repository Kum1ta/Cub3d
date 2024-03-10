/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:39:50 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/04 01:39:50 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	ft_putnbr_hexa_lower(unsigned int nb)
{
	if (nb >= 16)
		ft_putnbr_hexa_lower(nb / 16);
	write(1, &"0123456789abcdef"[nb % 16], 1);
}

static void	ft_putnbr_hexa_upper(unsigned int nb)
{
	if (nb >= 16)
		ft_putnbr_hexa_upper(nb / 16);
	write(1, &"0123456789ABCDEF"[nb % 16], 1);
}

void	ft_putnbr_hexa(unsigned int nb, int c)
{
	if (c == 'X')
		ft_putnbr_hexa_upper(nb);
	else if (c == 'x')
		ft_putnbr_hexa_lower(nb);
}
