/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:15:34 by edbernar          #+#    #+#             */
/*   Updated: 2023/11/04 00:15:34 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../libft.h"

int		ft_printf(const char *str, ...);

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen_fp(const char *str);
void	ft_putnbr_fd(int n, int fd);

int		ft_addrlen(unsigned long int addr, int *len);
void	ft_nbrhexalen(unsigned int nb, int *len);
void	ft_putnbr_hexa(unsigned int nb, int c);
void	ft_print_addr(unsigned long int addr);
void	ft_put_unsigned_int(unsigned int n);
int		ft_nbrlen(long int nbr);

#endif