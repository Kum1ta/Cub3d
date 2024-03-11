/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:06:13 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:35:09 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_Int.h"

bool	ft_is_conversion_flag(char c)
{
	if (c == '%' || c == 'c' || c == 's')
		return (true);
	else if (c == 'd' || c == 'i' || c == 'u')
		return (true);
	else if (c == 'x' || c == 'X' || c == 'p')
		return (true);
	return (false);
}

void	ft_parse_conversion_flag(char flag, int *j, t_print_format *data)
{
	data->flag = flag;
	if (flag == 'c' || flag == '%')
		data->conversion = &ft_printf_char;
	else if (flag == 's')
		data->conversion = &ft_printf_string;
	else if (flag == 'd' || flag == 'i')
		data->conversion = &ft_printf_int;
	else if (flag == 'u')
		data->conversion = &ft_printf_uint;
	else if (flag == 'x' || flag == 'X')
		data->conversion = &ft_printf_hexa;
	else if (flag == 'p')
		data->conversion = &ft_printf_ptr;
	*j += 1;
}
