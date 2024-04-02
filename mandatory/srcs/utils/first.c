/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 21:54:20 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics/graphics.h"

void	*error_ptr(char *str, void *ret)
{
	ft_printf("Cube3d: %s\n", str);
	return (ret);
}

int	error_int(char *str, int ret)
{
	ft_printf("Cube3d: %s\n", str);
	return (ret);
}
