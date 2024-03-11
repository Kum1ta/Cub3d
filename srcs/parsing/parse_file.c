/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:42:19 by psalame           #+#    #+#             */
/*   Updated: 2024/03/11 23:08:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	empty_map_data(t_map *map)
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

t_map	*parse_file(char *filename)
{
	t_map	*res;

	(void) filename;
	res = malloc(sizeof(t_map));
	if (!res)
		return (NULL); // todo error case
	empty_map_data(res);
	return (res);
}