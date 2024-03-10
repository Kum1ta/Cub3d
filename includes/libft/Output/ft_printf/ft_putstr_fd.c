/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:00:06 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/04 15:03:38 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	while (s[++i])
		write(fd, &s[i], 1);
}
