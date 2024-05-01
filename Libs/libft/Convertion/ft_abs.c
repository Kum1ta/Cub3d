/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:18 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 17:27:49 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	ft_abs(int value)
{
	unsigned int	res;

	if (value >= 0)
		res = value;
	else
		res = -value;
	return (res);
}
