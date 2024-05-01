/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:22:52 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:25 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf_Int.h"

static int	ft_get_abs_int_size(int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		size = 1;
	while (nb != 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

static void	ft_print_padding(t_print_format *data, int *writted)
{
	ft_putchar_rep(' ', data->field_width - *writted, data->fd);
	if (data->field_width > *writted)
		*writted += (data->field_width - *writted);
}

static void	ft_printf_sign(int value, t_print_format *data)
{
	if (value < 0 || data->force_sign || data->space_sign)
	{
		if (value < 0)
			ft_putchar_fd('-', data->fd);
		else if (data->force_sign)
			ft_putchar_fd('+', data->fd);
		else
			ft_putchar_fd(' ', data->fd);
	}
}

int	ft_printf_int(t_print_format *data, va_list ap)
{
	int	value;
	int	writted;

	value = va_arg(ap, int);
	writted = ft_get_abs_int_size(value);
	if (!data->precision && data->padding_left)
	{
		data->precision_width = data->field_width;
		if (value < 0 || data->force_sign || data->space_sign)
			data->precision_width -= 1;
		data->precision = true;
	}
	if (data->precision && (data->precision_width > writted || value == 0))
		writted = data->precision_width;
	if (value < 0 || data->force_sign || data->space_sign)
		writted++;
	if (!data->padding_right && (!data->padding_left || data->precision))
		ft_print_padding(data, &writted);
	ft_printf_sign(value, data);
	if (!data->precision || (data->precision_width > 0 || value != 0))
		ft_putunbr_size(ft_abs(value), data->precision_width, data->fd);
	if (data->padding_right)
		ft_print_padding(data, &writted);
	return (writted);
}
