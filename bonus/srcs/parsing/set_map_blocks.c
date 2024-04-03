/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:06:53 by psalame           #+#    #+#             */
/*   Updated: 2024/04/03 14:15:18 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"
  #include <stdio.h>

static t_map_error_type	parse_map_char(t_map *map, char c, size_t x, size_t y)
{
	if (ft_isspace(c))
		map->blocks[y][x].type = EMPTY;
	else if (c == '0')
		map->blocks[y][x].type = FLOOR;
	else if (c == '1')
		map->blocks[y][x].type = WALL;
	else if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		map->blocks[y][x].type = FLOOR;
		if (map->playerPos.x != -1.0f)
			return (MAP_DUPLICATE_PLAYER_POS);
		map->playerPos.x = x;
		map->playerPos.y = y;
		map->playerPos.z = 0.0f;
		if (c == 'N')
			map->playerPos.h = 0.0f;
		else if (c == 'E')
			map->playerPos.h = 90.0f;
		else if (c == 'S')
			map->playerPos.h = 180.0f;
		else
			map->playerPos.h = 270.0f;
	}
	else if (c == 'D')
		map->blocks[y][x].type = DOOR;
	return (MAP_NO_ERROR);
}

t_map_error_type	set_map_blocks(t_map *map, t_list *lines)
{
	size_t				y;
	size_t				x;
	char				*line;
	t_map_error_type	res;

	y = 0;
	res = MAP_NO_ERROR;
	while (map->blocks[y])
	{
		x = 0;
		line = lines->content;
		while (line[x] && map->blocks[y][x].type != END)
		{
			res = parse_map_char(map, line[x], x, y);
			if (res != MAP_NO_ERROR)
				return (res);
			x++;
		}
		y++;
		lines = lines->next;
	}
	return (res);
}
