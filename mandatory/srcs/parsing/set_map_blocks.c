/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:06:53 by psalame           #+#    #+#             */
/*   Updated: 2024/04/20 15:33:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

static t_map_error_type	parse_map_char(t_map *map, char c, t_ivec2 pos)
{
	if (ft_isspace(c))
		map->blocks[pos.y][pos.x] = EMPTY;
	else if (c == '0')
		map->blocks[pos.y][pos.x] = FLOOR;
	else if (c == '1')
		map->blocks[pos.y][pos.x] = WALL;
	else if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		map->blocks[pos.y][pos.x] = FLOOR;
		if (map->player_pos.x != -1.0f)
			return (MAP_DUPLICATE_PLAYER_POS);
		map->player_pos.x = pos.x;
		map->player_pos.y = pos.y;
		map->player_pos.z = 0.0f;
		if (c == 'N')
			map->player_pos.h = 0.0f;
		else if (c == 'E')
			map->player_pos.h = 90.0f;
		else if (c == 'S')
			map->player_pos.h = 180.0f;
		else
			map->player_pos.h = 270.0f;
	}
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
		while (line[x] && map->blocks[y][x] != END)
		{
			res = parse_map_char(map, line[x], (t_ivec2){x, y});
			if (res != MAP_NO_ERROR)
				return (res);
			x++;
		}
		y++;
		lines = lines->next;
	}
	return (res);
}
