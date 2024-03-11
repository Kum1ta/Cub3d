/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:42:19 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:54:17 by psalame          ###   ########.fr       */
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
	map->texture.ceiling[0] = -1;
	map->playerPos.x = -1.0f;
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
	if (!fd)
	{
		free(res);
		ft_dprintf(2, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	// todo parsing map
	close(fd);
	return (res);
}
