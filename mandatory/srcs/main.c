/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/26 18:13:24 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac > 2)
	{
		ft_dprintf(2, "Error\nToo many arguments.\n");
		return (1);
	}
	map = parse_map(av[1]);
	if (!map)
		return (0);
	graphics_part(map);
	free_map(map);
	return (1);
}
