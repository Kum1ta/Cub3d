/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:23:29 by psalame           #+#    #+#             */
/*   Updated: 2024/04/26 13:11:20 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static inline int	max(int a, int b)
{
	if (b > a)
		return (b);
	else
		return (a);
}

static inline int	calc_distshadow(float dist, int colorRaw)
{
	int		color_min[3];
	int		color[3];

	color_min[0] = max(0, ((colorRaw & 0x00FF0000) >> 16) - 60);
	color_min[1] = max(0, ((colorRaw & 0x0000FF00) >> 8) - 60);
	color_min[2] = max(0, ((colorRaw & 0x000000FF) - 60));
	color[0] = max(color_min[0], ((colorRaw & 0x00FF0000) >> 16) - dist * 5);
	color[1] = max(color_min[1], ((colorRaw & 0x0000FF00) >> 8) - dist * 5);
	color[2] = max(color_min[2], (colorRaw & 0x000000FF) - dist * 5);
	colorRaw = 255 << 24 | color[0] << 16 | color[1] << 8 | color[2];
	return (colorRaw);
}

static inline float	get_scalling_factor(t_raydata *ray, t_mlx *mlx)
{
	float	factor;

	if (ray->block->type == DOOR)
		mlx->tmp = &mlx->textures->door;
	else if (ray->dir == 3)
		mlx->tmp = &mlx->textures->north;
	else if (ray->dir == 0)
		mlx->tmp = &mlx->textures->east;
	else if (ray->dir == 1)
		mlx->tmp = &mlx->textures->south;
	else
		mlx->tmp = &mlx->textures->west;
	factor = (float)((t_img *)mlx->tmp)->height / mlx->stg->height * ray->dist;
	return (factor);
}

static inline int	get_scalling_y(t_raydata *ray, t_mlx *mlx,
									t_vec3 *img_pos, float factor)
{
	int	y;

	y = ray->wall_start - 1;
	if (y + mlx->map->cam_dir.z < 0)
		y = 0 - mlx->map->cam_dir.z - 1;
	img_pos->y = ((y + 1) - (mlx->stg->height - ray->wall_size) / 2)
		* factor;
	while (img_pos->y < 0)
		img_pos->y += ((t_img *)mlx->tmp)->height;
	return (y);
}

void	scalling(t_raydata *ray, t_mlx *mlx, int x)
{
	int		y;
	int		k;
	t_vec3	img_pos;
	int		color;

	img_pos.z = get_scalling_factor(ray, mlx);
	k = -1;
	img_pos.x = ray->img_x_percent * ((t_img *)mlx->tmp)->width;
	while (++k < mlx->stg->quality)
	{
		y = get_scalling_y(ray, mlx, &img_pos, img_pos.z);
		while (++y < fmin(ray->wall_end,
				mlx->stg->height - mlx->map->cam_dir.z))
		{
			img_pos.y += img_pos.z;
			color = get_ss_color(mlx, img_pos.x,
					((int) img_pos.y) % ((t_img *)mlx->tmp)->height, ray->dist);
			color = calc_distshadow(ray->dist, color);
			mlx_pixel_put(mlx->mlx, mlx->win, x + k, y + mlx->map->cam_dir.z,
				color);
		}
	}
}
