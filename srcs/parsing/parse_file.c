/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:42:19 by psalame           #+#    #+#             */
/*   Updated: 2024/03/13 19:00:02 by psalame          ###   ########.fr       */
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

static inline bool	is_map_valid(t_map *map)
{
	bool res;

	res = map->texture.north && map->texture.south
		&& map->texture.east && map->texture.west && map->playerPos.x != -1.0f
		&& map->texture.floor[0] != -1 && map->texture.ceiling[0] != -1;
	if (!res)
		ft_dprintf(2, "Error\nMissing map parameter.\n");
	return (res);
}

static bool	check_file_ext(char *filename, char *ext)
{
	size_t	filename_size;
	size_t	ext_size;

	if (!filename)
	{
		ft_dprintf(2, "Error\nfilename cannot be NULL\n");
		return (false);
	}
	filename_size = ft_strlen(filename);
	ext_size = ft_strlen(ext);
	if (filename_size < ext_size)
		return (false);
	if (ft_strncmp(filename + filename_size - ext_size, ext, ext_size) == 0)
		return (true);
	else
	{
		ft_dprintf(2, "Error\nBad file extention\n");
		return (false);
	}
}

t_map	*parse_map(char *filename)
{
	t_map	*res;
	char	fd;

	if (!check_file_ext(filename, ".cub"))
		return (NULL);
	res = malloc(sizeof(t_map));
	if (!res)
		ft_dprintf(2, "Error\n%s\n", strerror(ENOMEM));
	if (!res)
		return (NULL);
	empty_map_data(res);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(res);
		ft_dprintf(2, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	if (!parse_lines(fd, res) || !is_map_valid(res))
	{
		free_map(res);
		res = NULL;
	}
	close(fd);
	return (res);
}
