/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_rep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:02:55 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 18:39:32 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar_rep(char
static inline bool	check_map_line(char *line, t_list **map_lines)
{
	
} c, int rep, int fd)
{
	while (rep > 0)
	{
		write(fd, &c, 1);
		rep--;
	}
}
