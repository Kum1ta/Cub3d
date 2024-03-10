/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:31:25 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/04 01:31:25 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	ft_putaddr(unsigned long int nb)
{
	if (nb >= 16)
		ft_putaddr(nb / 16);
	write(1, &"0123456789abcdef"[nb % 16], 1);
}

void	ft_print_addr(unsigned long int addr)
{
	if (addr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return ;
	}
	ft_putstr_fd("0x", 1);
	ft_putaddr(addr);
}
