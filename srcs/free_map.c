/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:36:29 by psalame           #+#    #+#             */
/*   Updated: 2024/03/12 20:39:50 by psalame          ###   ########.fr       */
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
