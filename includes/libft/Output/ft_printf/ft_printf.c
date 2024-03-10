/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:52:06 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/03 16:52:06 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static int	args_len(va_list args, int c)
{
	int	len;

	len = 0;
	if (c == 'c')
	{
		va_arg(args, int);
		return (1);
	}
	else if (c == 'd' || c == 'i')
		return (ft_nbrlen((long int)va_arg(args, int)));
	else if (c == 'u')
		return (ft_nbrlen((long int)va_arg(args, unsigned int)));
	else if (c == 's')
		return (ft_strlen_fp(va_arg(args, char *)));
	else if (c == 'p')
	{
		if (ft_addrlen(va_arg(args, unsigned long int), &len) == -1)
			return (5);
		return (len + 2);
	}
	else if (c == 'x' || c == 'X')
		ft_nbrhexalen(va_arg(args, int), &len);
	else if (c == '%')
		return (1);
	return (len);
}

static int	format_print(va_list args, int c, va_list args_copy)
{
	if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'u')
		ft_put_unsigned_int(va_arg(args, unsigned int));
	else if (c == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'p')
		ft_print_addr(va_arg(args, unsigned long int));
	else if (c == 'x' || c == 'X')
		ft_putnbr_hexa(va_arg(args, int), c);
	else if (c == '%')
		ft_putchar_fd('%', 1);
	return (args_len(args_copy, c));
}

static int	print_and_len(va_list args, const char *str, int *i, int *len)
{
	va_list	copy_args;

	if (str[*i] == '%' && str[*i + 1])
	{
		va_copy(copy_args, args);
		*len += format_print(copy_args, str[*i += 1], args);
		va_end(copy_args);
	}
	else if (str[*i] == '%' && !str[*i + 1])
		return (-1);
	else
	{
		ft_putchar_fd(str[*i], 1);
		*len += 1;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = -1;
	len = 0;
	va_start(args, str);
	while (str[++i])
	{
		if (print_and_len(args, str, &i, &len) == -1)
			return (-1);
	}
	va_end(args);
	return (len);
}
