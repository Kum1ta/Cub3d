/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:16:48 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:39:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putunbr_fd(unsigned int nb, int fd)
{
	char			c;
	short			len;

	len = 0;
	if (nb >= 10)
		len += ft_putunbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	len += write(fd, &c, 1);
	return (len);
}
