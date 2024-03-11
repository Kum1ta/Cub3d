/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:20:08 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf_Int.h"

static int	ft_get_ulongbase_size(unsigned long nb, int base_len)
{
	int	size;

	size = 0;
	if (nb == 0)
		size = 1;
	while (nb != 0)
	{
		size++;
		nb /= base_len;
	}
	return (size);
}

static void	ft_putxlong_size(unsigned long nb, int precision, int fd)
{
	const char	*base = "0123456789abcdef";
	static int	current_width = 0;
	char		c;

	current_width++;
	c = base[nb % 16];
	if (nb / 16 != 0)
		ft_putxlong_size(nb / 16, precision, fd);
	else
	{
		while (current_width++ < precision)
			write(fd, base, 1);
		current_width = 0;
	}
	write(fd, &c, 1);
}

static void	ft_print_padding(t_print_format *data, int *writted)
{
	if (data->field_width > *writted)
	{
		ft_putchar_rep(' ', data->field_width - *writted, data->fd);
		*writted += (data->field_width - *writted);
	}
}

static void	ft_print_hexa_prefix(t_print_format *data)
{
	if (data->force_sign)
		ft_putchar_fd('+', data->fd);
	else if (data->space_sign)
		ft_putchar_fd(' ', data->fd);
	ft_putstr_fd("0x", data->fd);
}

int	ft_printf_ptr(t_print_format *data, va_list ap)
{
	void	*value;
	int		writted;

	value = va_arg(ap, void *);
	if (value == NULL)
		return (ft_printf_string_process(data, "(nil)", true));
	writted = ft_get_ulongbase_size((unsigned long) value, 16);
	if (!data->precision && data->padding_left)
	{
		data->precision_width = data->field_width - 2;
		if (data->space_sign || data->force_sign)
			data->precision_width -= 1;
		data->precision = true;
	}
	if (data->precision && data->precision_width > writted)
		writted = data->precision_width;
	writted += 2 + (data->space_sign || data->force_sign) * 1;
	if (!data->padding_right)
		ft_print_padding(data, &writted);
	ft_print_hexa_prefix(data);
	ft_putxlong_size((unsigned long) value, data->precision_width, data->fd);
	if (data->padding_right)
		ft_print_padding(data, &writted);
	return (writted);
}
