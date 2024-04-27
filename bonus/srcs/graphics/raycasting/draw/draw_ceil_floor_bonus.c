/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_floor_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:55:55 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:05:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static inline int	color_rgb_to_int(int rgb[3], int alpha)
{
	return (alpha << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	put_celling_floor(t_mlx *mlx, t_raydata *ray, int i)
{
	int		j;
	int		k;
	int		color;

	k = -1;
	while (++k < mlx->stg->quality && i + k < mlx->stg->width)
	{
		j = -mlx->map->cam_dir.z - 1;
		while (++j < ray->wall_start
			&& j + mlx->map->cam_dir.z < mlx->stg->height)
		{
			color = color_rgb_to_int(mlx->map->texture.ceiling, 255);
			mlx_pixel_put(mlx->mlx, mlx->win, i + k,
				j + mlx->map->cam_dir.z, color);
		}
		j += ray->wall_size - 1;
		while (++j + mlx->map->cam_dir.z < mlx->stg->height)
		{
			color = color_rgb_to_int(mlx->map->texture.floor, 255);
			mlx_pixel_put(mlx->mlx, mlx->win, i + k,
				j + mlx->map->cam_dir.z, color);
		}
	}
}
