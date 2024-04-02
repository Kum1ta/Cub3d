/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:00:06 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/11 23:33:08 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return (write(fd, s, ft_strlen(s)));
	return (write(fd, "(null)", 6));
}
