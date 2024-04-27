/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:36:29 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_blocks(t_block **blocks)
{
	size_t	i;

	if (blocks)
	{
		i = 0;
		while (blocks[i])
			free(blocks[i++]);
		free(blocks);
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		free_blocks(map->blocks);
		free(map->texture.north);
		free(map->texture.south);
		free(map->texture.east);
		free(map->texture.west);
		free(map);
	}
}
