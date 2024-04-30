/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:29:54 by psalame           #+#    #+#             */
/*   Updated: 2024/04/30 13:44:53 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

static inline void	init_ray(t_ray *ray, t_mlx *mlx, int screen_x, t_vec3 start)
{
	float	cam_x;

	cam_x = 2 * screen_x / (float) mlx->stg->width - 1;
	ray->dir_x = mlx->map->cam_dir.x + mlx->map->cam_plane.x * cam_x;
	ray->dir_y = mlx->map->cam_dir.y + mlx->map->cam_plane.y * cam_x;
	ray->pos_x = (int) start.x;
	ray->pos_y = (int) start.y;
	ray->delta_dist.x = fabs(1 / ray->dir_x);
	ray->delta_dist.y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
		ray->dist.x = (start.x - ray->pos_x) * ray->delta_dist.x;
	else
		ray->dist.x = (ray->pos_x + 1 - start.x) * ray->delta_dist.x;
	if (ray->dir_y < 0)
		ray->dist.y = (start.y - ray->pos_y) * ray->delta_dist.y;
	else
		ray->dist.y = (ray->pos_y + 1 - start.y) * ray->delta_dist.y;
	ray->step_x = 1 - 2 * (ray->dir_x < 0);
	ray->step_y = 1 - 2 * (ray->dir_y < 0);
	ray->nb_step = 0;
	ray->curr_size = 0;
}

static inline bool	mv_forward_ray(t_mlx *mlx, t_ray *ray,
									t_raydata *res, bool catch_interract)
{
	if (ray->dist.x < ray->dist.y)
	{
		ray->dist.x += ray->delta_dist.x;
		ray->pos_x += ray->step_x;
		ray->dir = 0;
	}
	else
	{
		ray->dist.y += ray->delta_dist.y;
		ray->pos_y += ray->step_y;
		ray->dir = 1;
	}
	if (ray->pos_x >= 0 && ray->pos_y >= 0
		&& (size_t)ray->pos_x < mlx->map->width
		&& (size_t)ray->pos_y < mlx->map->height)
	{
		res->block = &(mlx->map->blocks[ray->pos_y][ray->pos_x]);
		return ((res->block->type == WALL
				&& res->block->data.wall > ray->curr_size)
			|| (res->block->type == DOOR
				&& (res->block->data.door == false || catch_interract)
				&& ray->curr_size == 0));
	}
	return (false);
}

static inline void	get_wall_data(t_ray *ray, t_raydata *res, t_vec3 start)
{
	res->found = true;
	res->pos.x = ray->pos_x;
	res->pos.y = ray->pos_y;
	if (ray->dir == 0)
	{
		res->dist = ray->dist.x - ray->delta_dist.x;
		res->dir = ray->dir + 2 * (ray->step_x == -1);
		res->img_x_percent = start.y + res->dist * ray->dir_y;
	}
	else
	{
		res->dist = ray->dist.y - ray->delta_dist.y;
		res->dir = ray->dir + 2 * (ray->step_y == -1);
		res->img_x_percent = start.x + res->dist * ray->dir_x;
	}
	res->img_x_percent = res->img_x_percent - ((int) res->img_x_percent);
	ray->curr_size++;
	if (res->dir == 1 || res->dir == 2)
		res->img_x_percent = 1 - res->img_x_percent;
	if (res->block->type == WALL)
		ray->curr_size = res->block->data.wall;
}

t_raydata	*raycast(t_mlx *mlx, int screen_x,
				bool catch_interract, t_vec3 start)
{
	t_raydata	*res;
	t_ray		ray;
	int			i;
	int			max_height;

	max_height = MAX_HEIGHT;
	if (catch_interract)
		max_height = 1;
	res = malloc(max_height * sizeof(t_raydata));
	if (!res)
		return (NULL);
	i = 0;
	init_ray(&ray, mlx, screen_x, start);
	while (ray.curr_size < max_height && ray.nb_step < MAX_DISTANCE)
	{
		if (mv_forward_ray(mlx, &ray, res + i, catch_interract))
		{
			get_wall_data(&ray, res + i, start);
			i++;
		}
		ray.nb_step++;
	}
	while (i < max_height)
		res[i++].found = false;
	return (res);
}
