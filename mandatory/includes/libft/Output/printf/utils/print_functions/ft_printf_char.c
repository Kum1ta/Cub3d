/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:47:35 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:21 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf_Int.h"

int	ft_printf_char(t_print_format *data, va_list ap)
{
	char	c;
	int		printed;

	if (data->flag == '%')
	{
		write(data->fd, &data->flag, 1);
		return (1);
	}
	if (!data->padding_right)
		ft_putchar_rep(' ', data->field_width - 1, data->fd);
	c = va_arg(ap, int);
	write(data->fd, &c, 1);
	if (data->padding_right)
		ft_putchar_rep(' ', data->field_width - 1, data->fd);
	printed = 1;
	if (data->field_width != 0)
		printed += data->field_width - 1;
	return (printed);
}
