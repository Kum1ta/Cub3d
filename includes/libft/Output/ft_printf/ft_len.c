/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:30:37 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/04 14:30:37 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_nbrlen(long int nbr)
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

int	ft_addrlen(unsigned long int addr, int *len)
{
	if (addr == 0)
		return (-1);
	while (addr)
	{
		addr /= 16;
		*len += 1;
	}
	return (*len);
}

void	ft_nbrhexalen(unsigned int nb, int *len)
{
	if (nb >= 16)
		ft_nbrhexalen(nb / 16, len);
	*len += 1;
}
