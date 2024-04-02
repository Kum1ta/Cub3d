/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:00:02 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:45:45 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf_Int.h"

int	ft_printf_string_process(t_print_format *data,
						char *str,
						bool is_null)
{
	int		writted;
	int		strlen;

	strlen = ft_strlen(str);
	if (data->precision)
	{
		if (is_null)
		{
			if (ft_strncmp(str, "(nil)", 5) != 0)
				if (data->precision_width < strlen)
					strlen = 0;
		}
		else if (data->precision_width < strlen)
			strlen = data->precision_width;
	}
	writted = strlen;
	if (!data->padding_right)
		ft_putchar_rep(' ', data->field_width - strlen, data->fd);
	write(data->fd, str, strlen);
	if (data->padding_right)
		ft_putchar_rep(' ', data->field_width - strlen, data->fd);
	if (data->field_width > strlen)
		writted += data->field_width - strlen;
	return (writted);
}

int	ft_printf_string(t_print_format *data, va_list ap)
{
	char	*str;
	int		res;

	str = va_arg(ap, char *);
	if (str == NULL)
	{
		str = "(null)";
		res = ft_printf_string_process(data, str, true);
	}
	else
		res = ft_printf_string_process(data, str, false);
	return (res);
}
