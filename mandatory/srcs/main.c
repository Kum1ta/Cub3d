/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/30 13:23:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	verif_file(t_map *map)
{
	const char	*lst[4] = {
		map->texture.north,
		map->texture.south,
		map->texture.east,
		map->texture.west,
	};
	int			i;
	int			fd;

	i = -1;
	while (++i < 4)
	{
		fd = open(lst[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Error: Cannot open texture file.\n", 2);
			return (false);
		}
		close(fd);
	}
	return (true);
}

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
	if (verif_file(map))
		graphics_part(map);
	free_map(map);
	return (1);
}
