/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:56:47 by edbernar          #+#    #+#             */
/*   Updated: 2023/10/30 17:05:04 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *pointer, size_t size)
{
	unsigned int		i;
	char				*ptr;

	i = 0;
	ptr = (char *)pointer;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
}
