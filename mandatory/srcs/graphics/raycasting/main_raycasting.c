/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 22:08:06 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	calcul_wall_size(t_raydata *ray)
{
	if (!ray->found)
	{
		ray->wall_size = 0;
		ray->wall_start = HEIGHT / 2;
		ray->wall_end = HEIGHT / 2;
		return ;
	}
	if (ray->dist < 0.2)
		ray->dist = 0.2;
	ray->wall_size = (HEIGHT / ray->dist);
	if (ray->wall_size > HEIGHT)
		ray->wall_size = HEIGHT;
	ray->wall_start = (HEIGHT - (ray->wall_size)) / 2;
	ray->wall_end = (HEIGHT + ray->wall_size) / 2;
	ray->wall_start = ray->wall_start - ((ray->wall_end - ray->wall_start)
			* (WALL_SIZE - 1));
}

void	put_celling_floor(t_mlx *mlx, t_raydata *ray, int i)
{
	int		j;
	int		color;

	j = 0;
	while (j < ray->wall_start)
	{
		color = 255 << 24 | mlx->map->texture.ceiling[0] << 16
			| mlx->map->texture.ceiling[1] << 8
			| mlx->map->texture.ceiling[2];
		mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
		j++;
	}
	j += ray->wall_size;
	while (j < HEIGHT)
	{
		color = 255 << 24 | mlx->map->texture.floor[0] << 16
			| mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
		mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
		j++;
	}
}

void	scalling(t_raydata *ray, t_mlx *mlx, int i, float factor)
{
	int		color;
	int		j;
	float	wall_size;
	int		imgx;
	float	imgy;

	j = ray->wall_start;
	if (ray->dir == 0)
		mlx->tmp = &mlx->textures->north;
	else if (ray->dir == 1)
		mlx->tmp = &mlx->textures->east;
	else if (ray->dir == 2)
		mlx->tmp = &mlx->textures->south;
	else
		mlx->tmp = &mlx->textures->west;
	imgx = ray->imgx_percent * mlx->tmp->width;
	wall_size = HEIGHT / ray->dist;
	imgy = (j - (HEIGHT - wall_size) / 2) * factor;
	while (j < ray->wall_end)
	{
		color = mlx_get_image_pixel(mlx->mlx, mlx->tmp->img, imgx, (int)imgy);
		imgy += factor;
		mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
		j++;
	}
}

void	draw_column(t_mlx *mlx, t_raydata **ray)
{
	float	factor;
	int		i;

	i = -1;
	while (++i < WIDTH)
	{
		put_celling_floor(mlx, ray[i], i);
		if (ray[i]->found)
		{
			factor = HEIGHT / ray[i]->dist;
			if (ray[i]->dir == 0)
				factor = (float)mlx->textures->north.height / factor;
			else if (ray[i]->dir == 1)
				factor = (float)mlx->textures->east.height / factor;
			else if (ray[i]->dir == 2)
				factor = (float)mlx->textures->south.height / factor;
			else
				factor = (float)mlx->textures->west.height / factor;
			scalling(ray[i], mlx, i, factor);
		}
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	t_raydata	*ray[WIDTH];
	float		angle[WIDTH];
	int			i;

	if (need_free)
		return ;
	i = -1;
	while (++i < WIDTH)
	{
		angle[i] = (mlx->map->player_pos.h - FOV / 2
				+ (float)i / (float)WIDTH * FOV) - 90;
		ajust_angle(&angle[i]);
		ray[i] = raycast(mlx, angle[i]);
		if (!ray[i])
		{
			free_ray(ray);
			return ;
		}
		correct_fish_eye(ray[i], angle[i], mlx);
		calcul_wall_size(ray[i]);
	}
	draw_column(mlx, ray);
}
