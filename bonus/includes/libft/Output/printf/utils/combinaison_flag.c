/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combinaison_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:18:59 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:13 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_Int.h"
#include <limits.h>

bool	ft_is_combinaison_flag(char c)
{
	if (ft_isdigit(c) || c == '-' || c == '.' || c == '*')
		return (true);
	else if (c == '+' || c == '#' || c == ' ')
		return (true);
	return (false);
}

static void	ft_parse_field_width(const char *str, t_print_format *data, int *j)
{
	long	tmp_value;

	tmp_value = 0;
	while (ft_isdigit(str[*j]))
	{
		tmp_value = tmp_value * 10 + (str[*j] - '0');
		if (tmp_value > INT_MAX)
		{
			data->error = true;
			tmp_value = -1;
			break ;
		}
		*j += 1;
	}
	*j -= 1;
	if (data->precision)
		data->precision_width = tmp_value;
	else
		data->field_width = tmp_value;
}

static void	ft_get_arg_width(t_print_format *data, va_list ap)
{
	int	width;

	width = va_arg(ap, int);
	if (width == INT_MIN)
	{
		data->error = true;
		data->field_width = -1;
	}
	else if (data->precision)
	{
		if (width < 0)
			data->precision = false;
		else
			data->precision_width = width;
	}
	else
	{
		if (width < 0)
		{
			data->padding_left = false;
			data->padding_right = true;
			width = -width;
		}
		data->field_width = width;
	}
}

void	ft_parse_combinaison_flag(const char *str,
							t_print_format *data,
							int *j,
							va_list ap)
{
	if (ft_isdigit(str[*j]) && \
		(str[*j] != '0' || (data->precision || data->padding_right)))
		ft_parse_field_width(str, data, j);
	else if (str[*j] == '*')
		ft_get_arg_width(data, ap);
	else if (str[*j] != '.' && data->precision)
		data->error = 1;
	else if (str[*j] != '.' && str[*j] != '-' && data->padding_right)
		data->error = 1;
	else if (str[*j] == '0')
		data->padding_left = true;
	else if (str[*j] == '-')
		data->padding_right = true;
	else if (str[*j] == '.')
		data->precision = true;
	else if (str[*j] == '#')
		data->alternative_form = true;
	else if (str[*j] == ' ')
		data->space_sign = true;
	else if (str[*j] == '+')
		data->force_sign = true;
	*j += 1;
}
