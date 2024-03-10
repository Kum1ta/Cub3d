/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:31 by edbernar          #+#    #+#             */
/*   Updated: 2023/12/02 23:47:27 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

size_t	ft_strlen_fp(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (6);
	while (str[i])
		i++;
	return (i);
}
