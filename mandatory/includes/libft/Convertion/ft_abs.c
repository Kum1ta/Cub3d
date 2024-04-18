/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:18 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 13:50:29 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint16_t	ft_abs(int value)
{
	unsigned int	res;

	if (value >= 0)
		res = value;
	else
		res = -value;
	return (res);
}
