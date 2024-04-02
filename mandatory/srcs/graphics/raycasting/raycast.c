/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:06:32 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 22:17:11 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	init_ray(t_ray *ray, t_mlx *mlx, float angle)
{
	ray->r_angle = angle * PI / 180;
	ray->dirx = cos(ray->r_angle);
	ray->diry = sin(ray->r_angle);
	ray->posx = (int) mlx->map->playerPos.x;
	ray->posy = (int) mlx->map->playerPos.y;
	ray->deltadx = sqrt(1 + (ray->diry * ray->diry) / (ray->dirx * ray->dirx));
	ray->deltady = sqrt(1 + (ray->dirx * ray->dirx) / (ray->diry * ray->diry));
	if (ray->dirx < 0)
		ray->distx = (mlx->map->playerPos.x - ray->posx) * ray->deltadx;
	else
		ray->distx = (ray->posx + 1 - mlx->map->playerPos.x) * ray->deltadx;
	if (ray->diry < 0)
		ray->disty = (mlx->map->playerPos.y - ray->posy) * ray->deltady;
	else
		ray->disty = (ray->posy + 1 - mlx->map->playerPos.y) * ray->deltady;
	ray->stepx = 1 - 2 * (ray->dirx < 0);
	ray->stepy = 1 - 2 * (ray->diry < 0);
	ray->nbstep = 0;
}

void	calcul_ray(t_ray *ray)
{
	if (ray->distx < ray->disty)
	{
		ray->distx += ray->deltadx;
		ray->posx += ray->stepx;
		ray->dir = 0;
	}
	else
	{
		ray->disty += ray->deltady;
		ray->posy += ray->stepy;
		ray->dir = 1;
	}
}

void	calcul_raydata(t_mlx *mlx, t_ray ray, t_raydata *res)
{
	if (ray.dir == 0)
	{
		res->dist = ray.distx - ray.deltadx;
		res->dir = ray.dir + 2 * (ray.stepx == -1);
		res->imgx_percent = mlx->map->playerPos.y + res->dist * ray.diry;
	}
	else
	{
		res->dist = ray.disty - ray.deltady;
		res->dir = ray.dir + 2 * (ray.stepy == -1);
		res->imgx_percent = mlx->map->playerPos.x + res->dist * ray.dirx;
	}
}

t_raydata	*raycast(t_mlx *mlx, float angle)
{
	t_raydata	*res;
	t_ray		ray;

	res = ft_calloc(1, sizeof(t_raydata));
	if (!res)
		return (NULL);
	init_ray(&ray, mlx, angle);
	while (!res->found && ray.nbstep < MAX_DISTANCE)
	{
		calcul_ray(&ray);
		if (ray.posx >= 0 && ray.posy >= 0 && ray.posx < (float)mlx->map->width
			&& ray.posy < (float)mlx->map->height
			&& mlx->map->blocks[ray.posy][ray.posx] == WALL)
		{
			res->found = true;
			calcul_raydata(mlx, ray, res);
			res->imgx_percent = res->imgx_percent - ((int) res->imgx_percent);
		}
		ray.nbstep++;
	}
	return (res);
}
