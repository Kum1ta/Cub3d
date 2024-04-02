/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:56:51 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf_Int.h"

static int	ft_get_uint_base_size(unsigned int nb, int base_len)
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

static void	ft_print_padding(t_print_format *data, int *writted)
{
	char	c;

	c = ' ';
	ft_putchar_rep(c, data->field_width - *writted, data->fd);
	if (data->field_width > *writted)
		*writted += (data->field_width - *writted);
}

static void	ft_putxnbr_size(unsigned int nb, bool maj, int precision, int fd)
{
	const char	*base = "0123456789abcdef";
	static int	current_width = 0;
	char		c;

	current_width++;
	c = base[nb % 16];
	if (maj)
		c = ft_toupper(c);
	if (nb / 16 != 0)
		ft_putxnbr_size(nb / 16, maj, precision, fd);
	else
	{
		while (current_width++ < precision)
			write(fd, base, 1);
		current_width = 0;
	}
	write(fd, &c, 1);
}

static void	ft_print_alternative_form(bool maj, int fd)
{
	if (maj)
		ft_putstr_fd("0X", fd);
	else
		ft_putstr_fd("0x", fd);
}

int	ft_printf_hexa(t_print_format *data, va_list ap)
{
	unsigned int	value;
	int				writted;

	value = va_arg(ap, unsigned int);
	writted = ft_get_uint_base_size(value, 16);
	if (!data->precision && data->padding_left)
	{
		data->precision_width = data->field_width - data->alternative_form * 2;
		data->precision = true;
	}
	if (data->precision && (data->precision_width > writted || value == 0))
		writted = data->precision_width;
	if (value != 0 && data->alternative_form)
		writted += 2;
	if (!data->padding_right)
		ft_print_padding(data, &writted);
	if (value != 0 && data->alternative_form)
		ft_print_alternative_form(data->flag == 'X', data->fd);
	if (!data->precision || (data->precision_width > 0 || value != 0))
		ft_putxnbr_size(value, data->flag == 'X', data->precision_width, \
			data->fd);
	if (data->padding_right)
		ft_print_padding(data, &writted);
	return (writted);
}
