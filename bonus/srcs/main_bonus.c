/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/26 18:14:21 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verif_start_video(void)
{
	char	str[37];
	int		i;

	i = 0;
	ft_strncpy(str, "textures/main_menu/video/1/000.png\0", 36);
	while (i < 102)
	{
		str[27] = i / 100 + '0';
		str[28] = i / 10 % 10 + '0';
		str[29] = i % 10 + '0';
		if (access(str, R_OK) == -1 || access(str, F_OK) == -1)
			return (ft_putstr_fd("Error: Video file\n", 2));
		i++;
	}
	return (0);
}

static int	verif_file(t_map *map)
{
	int			i;
	const char	*lst[13] = {
		map->texture.north,
		map->texture.south,
		map->texture.east,
		map->texture.west,
		"textures/game/fire.png",
		"textures/game/player_back.png",
		"textures/game/player_front.png",
		"textures/game/player_left.png",
		"textures/game/player_right.png",
		"textures/inventory/fist.png",
		"textures/inventory/knife.png",
		"textures/inventory/weapon.png",
		"textures/main_menu/bg_main_menu.png",
	};

	i = -1;
	while (++i < 13)
	{
		if (access(lst[i], R_OK) == -1 || access(lst[i], F_OK) == -1)
			return (ft_putstr_fd("Error: Texture file not found\n", 2));
	}
	return (verif_start_video());
}

int	main(int ac, char **av)
{
	t_settings	*settings;
	t_map		*map;

	if (ac > 2)
	{
		ft_dprintf(2, "Error\nToo many arguments.\n");
		return (1);
	}
	settings = parse_config_file(".config");
	if (!settings)
		return (1);
	map = parse_map(av[1], (int [2]){settings->width, settings->height});
	if (!map)
	{
		free(settings);
		return (1);
	}
	if (verif_file(map))
	{
		free_map(map);
		free(settings);
		return (1);
	}
	graphics_part(map, settings);
}
