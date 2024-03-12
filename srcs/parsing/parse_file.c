/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:42:19 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 23:50:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"
#include <string.h>
#include <errno.h>

static inline void	empty_map_data(t_map *map)
{
	map->blocks = NULL;
	map->texture.north = NULL;
	map->texture.south = NULL;
	map->texture.east = NULL;
	map->texture.west = NULL;
	map->texture.floor[0] = -1;
	map->texture.floor[1] = -1;
	map->texture.floor[2] = -1;
	map->texture.ceiling[0] = -1;
	map->texture.ceiling[1] = -1;
	map->texture.ceiling[2] = -1;
	map->playerPos.x = -1.0f;
}

static bool	can_exit_map(t_block **blocks, int x, int y)
{
	t_block	current;
	bool	escaped;

	if (blocks[y] == NULL || y == 0 || x == 0 || blocks[y][x] != FLOOR)
		return (true);
	current = blocks[y][x];
	blocks[y][x] = WALL;
	escaped = false;
	if (!escaped && blocks[y - 1][x] != WALL)
		escaped = can_exit_map(blocks, x, y - 1);
	if (!escaped && blocks[y + 1][x] != WALL)
		escaped |= can_exit_map(blocks, x, y + 1);
	if (!escaped && blocks[y][x - 1] != WALL)
		escaped |= can_exit_map(blocks, x - 1, y);
	if (!escaped && blocks[y][x + 1] != WALL)
		escaped |= can_exit_map(blocks, x + 1, y);
	blocks[y][x] = current;
	return (escaped);
}

static inline bool	is_map_valid(t_map *map)
{
	return (map->texture.north && map->texture.south
		&& map->texture.east && map->texture.west && map->playerPos.x != -1.0f
		&& map->texture.floor[0] != -1 && map->texture.ceiling[0] != -1
		&& !can_exit_map(map->blocks, map->playerPos.x, map->playerPos.y))
}

t_map	*parse_map(char *filename)
{
	t_map	*res;
	char	fd;

	res = malloc(sizeof(t_map));
	if (!res)
	{
		ft_dprintf(2, "Error\n%s\n", strerror(ENOMEM));
		return (NULL);
	}
	empty_map_data(res);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(res);
		ft_dprintf(2, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	if (!parse_lines(fd, res) || is_map_valid(res))
	{
		free_map(res);
		res = NULL;
	}
	close(fd);
	return (res);
}
