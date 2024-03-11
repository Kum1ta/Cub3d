/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:14:26 by psalame           #+#    #+#             */
/*   Updated: 2024/01/18 14:33:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_Int.h"

static void	ft_printf_err(t_printf_data *fdata,
						int j,
						t_print_format *data)
{
	const char	*str;

	str = fdata->str;
	if (str[j] == 0 || data->field_width == -1 || data->precision_width == -1)
	{
		fdata->writted_char = -1;
		fdata->i = ft_strlen(str);
	}
	else
	{
		ft_putchar_fd('%', 1);
		fdata->i += 1;
		fdata->writted_char += 1;
	}
}

static void	ft_formatf(t_printf_data *fdata, va_list ap)
{
	t_print_format	data;
	int				j;

	ft_bzero(&data, sizeof(data));
	j = fdata->i + 1;
	data.fd = fdata->fd;
	while (!data.error && data.conversion == NULL && fdata->str[j])
	{
		if (ft_is_combinaison_flag(fdata->str[j]))
			ft_parse_combinaison_flag(fdata->str, &data, &j, ap);
		else if (ft_is_conversion_flag(fdata->str[j]))
			ft_parse_conversion_flag(fdata->str[j], &j, &data);
		else
			data.error = true;
	}
	if (!data.flag || data.error)
		ft_printf_err(fdata, j, &data);
	else
	{
		fdata->writted_char += (*data.conversion)(&data, ap);
		fdata->i = j;
	}
}

int	ft_printf(const char *str, ...)
{
	t_printf_data	fdata;
	int				to_write;
	va_list			ap;

	va_start(ap, str);
	ft_bzero(&fdata, sizeof(t_printf_data));
	fdata.str = str;
	fdata.fd = 1;
	while (str[fdata.i])
	{
		if (str[fdata.i] == '%')
			ft_formatf(&fdata, ap);
		else
		{
			to_write = 0;
			while (str[fdata.i + to_write] != '\0'
				&& str[fdata.i + to_write] != '%')
				to_write++;
			write(1, str + fdata.i, to_write);
			fdata.writted_char += to_write;
			fdata.i += to_write;
		}
	}
	va_end(ap);
	return (fdata.writted_char);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	t_printf_data	fdata;
	int				to_write;
	va_list			ap;

	va_start(ap, str);
	ft_bzero(&fdata, sizeof(t_printf_data));
	fdata.str = str;
	fdata.fd = fd;
	while (str[fdata.i])
	{
		if (str[fdata.i] == '%')
			ft_formatf(&fdata, ap);
		else
		{
			to_write = 0;
			while (str[fdata.i + to_write] != '\0'
				&& str[fdata.i + to_write] != '%')
				to_write++;
			write(fd, str + fdata.i, to_write);
			fdata.writted_char += to_write;
			fdata.i += to_write;
		}
	}
	va_end(ap);
	return (fdata.writted_char);
}
