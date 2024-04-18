/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:06:53 by psalame           #+#    #+#             */
/*   Updated: 2024/04/02 22:05:02 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_int.h"

static t_map_error_type	parse_map_char(t_map *map, char c, size_t x, size_t y)
{
	if (ft_isspace(c))
		map->blocks[y][x] = EMPTY;
	else if (c == '0')
		map->blocks[y][x] = FLOOR;
	else if (c == '1')
		map->blocks[y][x] = WALL;
	else if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		map->blocks[y][x] = FLOOR;
		if (map->player_pos.x != -1.0f)
			return (MAP_DUPLICATE_PLAYER_POS);
		map->player_pos.x = x;
		map->player_pos.y = y;
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

bool	allocate_map(t_map *map)
{
	size_t	i;

	map->blocks = malloc((map->height + 1) * sizeof(t_block *));
	if (!map->blocks)
		return (false);
	i = 0;
	while (i < map->height)
	{
		map->blocks[i] = ft_calloc((map->width + 1), sizeof(t_block));
		if (map->blocks[i] == NULL)
		{
			free_blocks(map->blocks);
			map->blocks = NULL;
			return (false);
		}
		map->blocks[i][map->width] = END;
		i++;
	}
	map->blocks[i] = NULL;
	return (true);
}
