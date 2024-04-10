/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:58:29 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 16:42:15 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <unistd.h>

void	test_map(char *filename, int expected)
{
	ft_printf("\n\nTest for map %s : \n", filename);
	int res;
	t_map *map = parse_map(filename, (int [2]){1, 1});
	if (map)
	{
		ft_printf("\tnorth txt : %s\n", map->texture.north);
		ft_printf("\tsouth txt : %s\n", map->texture.south);
		ft_printf("\teast txt : %s\n", map->texture.east);
		ft_printf("\twest txt : %s\n", map->texture.west);
		ft_printf("\tfloor color R: %d, G: %d, B: %d\n", map->texture.floor[0], map->texture.floor[1], map->texture.floor[2]);
		ft_printf("\tceiling color R: %d, G: %d, B: %d\n", map->texture.ceiling[0], map->texture.ceiling[1], map->texture.ceiling[2]);
		printf("\tplayer pos : x: %f, y: %f, z: %f, h: %f\n", map->playerPos.x, map->playerPos.y, map->playerPos.z, map->playerPos.h);
		size_t	i = 0;
		while (map->blocks[i])
		{
			size_t	j = 0;
			while (map->blocks[i][j].type != END)
			{
				switch (map->blocks[i][j].type)
				{
					case EMPTY:
						write(1, " ", 1);
						break;
					case WALL:
						write(1, "1", 1);
						break;
					case FLOOR:
						write(1, "0", 1);
						break;
					case DOOR:
						write(1, "D", 1);
						break;
					case END:
						break;
				}
				j++;
			}
			ft_printf("\n");
			i++;
		}
		free_map(map);
		res = 0;
	}
	else
		res = 1;
	if (res != expected)
		ft_printf("\033[31mKO\n\033[0m");
	else
		ft_printf("\033[32mOK\n\033[0m");
}

int	main(void)
{
	test_map(NULL, 1);
	test_map("./invalid_file.cub", 1);
	test_map("./test_maps/duplicate_parameter.cub", 1);
	test_map("./test_maps/duplicate_parameter2.cub", 1);
	test_map("./test_maps/duplicate_player.cub", 1);
	test_map("./test_maps/empty_line.cub", 1);
	test_map("./test_maps/invalid_color.cub", 1);
	test_map("./test_maps/invalid_color2.cub", 1);
	test_map("./test_maps/invalid_color3.cub", 1);
	test_map("./test_maps/invalid_ext.txt", 1);
	test_map("./test_maps/invalid_map_chr.cub", 1);
	test_map("./test_maps/invalid_map.cub", 1);
	test_map("./test_maps/missing_parameter.cub", 1);
	test_map("./test_maps/no_player.cub", 1);
	test_map("./test_maps/unclosed_map.cub", 1);
	test_map("./test_maps/unclosed_map2.cub", 1);
	test_map("./test_maps/unclosed_map3.cub", 1);
	test_map("./test_maps/unclosed_map4.cub", 1);
	test_map("./test_maps/unclosed_map5.cub", 1);
	test_map("./test_maps/empty_file.cub", 1);
	test_map("./test_maps/valid_one.cub", 0);
	test_map("./test_maps/valid_two.cub", 0);
	test_map("./test_maps/valid_colorspace_todo.cub", 0);
}