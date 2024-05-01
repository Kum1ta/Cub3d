/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_Int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:33:44 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 17:23:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INT_H
# define FT_PRINTF_INT_H
# include "../../libft.h"
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_print_format
{
	int		(*conversion)(struct s_print_format *format_data, va_list ap);
	char	flag;
	bool	error;
	int		fd;
	int		field_width;
	bool	padding_left;
	bool	padding_right;
	int		precision_width;
	bool	precision;
	bool	alternative_form;
	bool	space_sign;
	bool	force_sign;
}	t_print_format;

typedef struct s_printf_data
{
	const char	*str;
	int			writted_char;
	int			i;
	int			fd;
}	t_printf_data;

// flags managment

bool	ft_is_combinaison_flag(char c);
void	ft_parse_combinaison_flag(
			const char *str,
			t_print_format *data,
			int *j,
			va_list ap);
bool	ft_is_conversion_flag(char c);
void	ft_parse_conversion_flag(char flag, int *j, t_print_format *data);

// print functions

int		ft_printf_char(t_print_format *data, va_list ap);
int		ft_printf_string_process(t_print_format *data,
			char *str,
			bool is_null);
int		ft_printf_string(t_print_format *data, va_list ap);
void	ft_putunbr_size(unsigned int nb, int precision, int fd);
int		ft_printf_int(t_print_format *data, va_list ap);
int		ft_printf_uint(t_print_format *data, va_list ap);
int		ft_printf_hexa(t_print_format *data, va_list ap);
int		ft_printf_ptr(t_print_format *data, va_list ap);

#endif