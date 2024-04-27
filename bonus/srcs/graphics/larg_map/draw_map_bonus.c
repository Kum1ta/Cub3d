/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:29:40 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 14:50:49 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

void	draw_square(t_mlx *mlx, int size, int color, int xy[2])
{
	int	i;
	int	j;

	i = xy[0];
	if (i < 0)
		i = 0;
	while (i < xy[0] + size && i < mlx->stg->width)
	{
		j = xy[1];
		if (j < 0)
			j = 0;
		while (j < xy[1] + size && j < mlx->stg->height - 100)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
			j++;
		}
		i++;
	}
}

void	put_player(t_mlx *mlx)
{
	int	i;
	int	k;

	i = mlx->menu_map->size * mlx->map->player_pos.y;
	k = mlx->menu_map->size * mlx->map->player_pos.x;
	draw_square(mlx, mlx->menu_map->size / 2, 0xFF0000FF,
		(int [2]){k + mlx->menu_map->x - mlx->menu_map->size / 4,
		i + mlx->menu_map->y - mlx->menu_map->size / 4});
}

void	fill_map(t_mlx *mlx)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	while (i < mlx->menu_map->size * mlx->map->height)
	{
		j = 0;
		while (j < mlx->menu_map->size * mlx->map->width)
		{
			if (mlx->map->blocks[i / mlx->menu_map->size][j
				/ mlx->menu_map->size].type == WALL)
				draw_square(mlx, mlx->menu_map->size, 0xFF454545, (int [2])
				{j + mlx->menu_map->x - 3, i + mlx->menu_map->y - 3});
			else if (mlx->map->blocks[i / mlx->menu_map->size][j
				/ mlx->menu_map->size].type == FLOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFFA1A1A1, (int [2])
				{j + mlx->menu_map->x, i + mlx->menu_map->y});
			else if (mlx->map->blocks[i / mlx->menu_map->size][j
				/ mlx->menu_map->size].type == DOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFF222222, (int [2])
				{j + mlx->menu_map->x - 3, i + mlx->menu_map->y - 3});
			j += mlx->menu_map->size;
		}
		i += mlx->menu_map->size;
	}
}
