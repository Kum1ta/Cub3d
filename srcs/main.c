/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/12 13:42:52 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_block map[4][5] = {
		{ WALL , WALL , WALL , WALL , END },
		{ WALL , FLOOR, FLOOR, WALL , END },
		{ WALL , WALL , FLOOR , WALL , END },
		{ EMPTY, WALL , WALL , WALL , END },
	};
	(void)ac;
	(void)av;
	(void)map;
	ft_printf("Hello world !");
}