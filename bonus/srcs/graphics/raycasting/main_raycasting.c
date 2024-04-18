/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 18:46:43 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	free_ray(t_raydata ***ray, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < mlx->stg->width)
		free(ray[i]);
}

void	calcul_wall_size(t_mlx *mlx, t_raydata *ray)
{
	int	tmp;
	int	i;

	i = -1;
	while (++i < MAX_HEIGHT)
	{
		if (!ray[i].found)
		{
			ray[i].wall_size = 0;
			ray[i].wall_start = mlx->stg->height / 2;
			ray[i].wall_end = mlx->stg->height / 2;
			continue ;
		}
		ray[i].wall_size = (mlx->stg->height / ray[i].dist);
		ray[i].wall_start = ((mlx->stg->height - ray[i].wall_size) / 2);
		ray[i].wall_end = ray[i].wall_start + ray[i].wall_size;
		if (ray[i].block->type == WALL)
			ray[i].wall_start = ray[i].wall_start
				- ((ray[i].wall_end - ray[i].wall_start)
					* (ray[i].block->data.wall - 1));
		else
			ray[i].wall_start = ray[i].wall_start;
	}
}

void	put_celling_floor(t_mlx *mlx, t_raydata *ray, int i)
{
	int		j;
	int		k;
	int		color;

	k = -1;
	while (++k < mlx->stg->quality)
	{
		j = -mlx->map->cam_dir.z - 1;
		while (++j < ray->wall_start)
		{
			color = 255 << 24 | mlx->map->texture.ceiling[0] << 16
				| mlx->map->texture.ceiling[1] << 8
				| mlx->map->texture.ceiling[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k,
				j + mlx->map->cam_dir.z, color);
		}
		j += ray->wall_size - 1;
		while (++j < mlx->stg->height - mlx->map->cam_dir.z)
		{
			color = 255 << 24 | mlx->map->texture.floor[0] << 16
				| mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k,
				j + mlx->map->cam_dir.z, color);
		}
	}
}

static inline void	send_rays(t_mlx *mlx, t_raydata **ray)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->stg->width)
	{
		if (i % mlx->stg->quality == 0)
		{
			ray[i] = raycast(mlx, i, false, mlx->map->player_pos);
			if (!ray[i])
				continue ;
			calcul_wall_size(mlx, ray[i]);
			j = MAX_HEIGHT - 1;
			while (j > 0 && !ray[i][j].found)
				j--;
			put_celling_floor(mlx, ray[i] + MAX_HEIGHT - 1, i);
			while (j >= 0)
			{
				if (ray[i] && ray[i][j].found)
					scalling(ray[i] + j, mlx, i, j);
				j--;
			}
		}
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	static t_raydata	**ray;
	int					i;

	if (need_free)
		free(ray);
	if (need_free)
		return ;
	while (!ray)
		ray = malloc(mlx->stg->width * sizeof(t_raydata *));
	send_rays(mlx, ray);
	mlx->center_sprite = draw_sprites(mlx, ray);
	put_fps(mlx, 0);
	item_effect(mlx, mlx->center_sprite);
	put_actual_item(mlx);
	if (mlx->stg->show_minimap)
		mini_map(mlx);
	inventory(mlx, 0);
	show_popup(mlx);
	i = -1;
	while (++i < mlx->stg->width)
		if (i % mlx->stg->quality == 0)
			free(ray[i]);
}
