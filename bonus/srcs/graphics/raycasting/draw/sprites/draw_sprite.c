/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:19:11 by psalame           #+#    #+#             */
/*   Updated: 2024/04/19 13:01:01 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites_Int.h"

static inline bool	draw_sprite_pixel(t_mlx *mlx, t_sprite *sprite,
									t_drawsprt_attr *draw_data)
{
	int		color;

	color = mlx_get_image_pixel(mlx->mlx, sprite->txt->img,
			draw_data->img_pos_x, draw_data->img_pos_y);
	if ((color >> 24 & 0xFF) == 0xFF)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, draw_data->pos_x,
			draw_data->pos_y + mlx->map->cam_dir.z, color);
		if (draw_data->pos_x == mlx->stg->width / 2
			&& draw_data->pos_y + mlx->map->cam_dir.z == mlx->stg->height / 2)
			return (true);
	}
	return (false);
}

static inline bool	draw_sprite_line(t_mlx *mlx, t_sprite *sprite,
									t_drawsprt_attr *draw_data)
{
	bool	touch_center;

	touch_center = false;
	draw_data->img_pos_x = ((float)(draw_data->pos_x - draw_data->start_x))
		/ ((float) sprite->screen_size[0]) * sprite->txt->width;
	draw_data->start_y = mlx->stg->height / 2 - sprite->screen_size[1] / 2;
	draw_data->pos_y = draw_data->start_y;
	if (draw_data->pos_y - draw_data->start_y < 0)
		draw_data->pos_y = -draw_data->start_y;
	while (draw_data->pos_y - draw_data->start_y < sprite->screen_size[1]
		&& draw_data->pos_y + mlx->map->cam_dir.z < mlx->stg->height)
	{
		draw_data->img_pos_y = ((float)(draw_data->pos_y - draw_data->start_y))
			/ ((float) sprite->screen_size[1]) * sprite->txt->height;
		if (draw_data->pos_y + mlx->map->cam_dir.z >= 0)
			draw_sprite_pixel(mlx, sprite, draw_data);
		touch_center |= draw_sprite_pixel(mlx, sprite, draw_data);
		draw_data->pos_y++;
	}
	return (touch_center);
}

static inline float	get_quality_ray_dist(t_mlx *mlx, t_raydata **ray, int x)
{
	x = x / mlx->stg->quality;
	x = x * mlx->stg->quality;
	return (ray[x]->dist);
}

bool	draw_sprite(t_mlx *mlx, t_sprite *sprite, t_raydata **ray)
{
	t_drawsprt_attr	draw_data;
	bool			touch_center;

	touch_center = false;
	sprite->screen_size[0] = mlx->stg->height / sprite->depth;
	sprite->screen_size[1] = mlx->stg->height / sprite->depth;
	if (sprite->depth > 0
		&& sprite->screen_x + sprite->screen_size[0] / 2 >= 0
		&& sprite->screen_x - sprite->screen_size[0] / 2 < mlx->stg->width)
	{
		draw_data.start_x = sprite->screen_x - sprite->screen_size[0] / 2;
		draw_data.pos_x = draw_data.start_x;
		if (draw_data.pos_x < 0)
			draw_data.pos_x = 0;
		while (draw_data.pos_x - draw_data.start_x < sprite->screen_size[0]
			&& draw_data.pos_x < mlx->stg->width)
		{
			if (draw_data.pos_x >= 0
				&& sprite->depth
				< get_quality_ray_dist(mlx, ray, draw_data.pos_x))
				touch_center |= draw_sprite_line(mlx, sprite, &draw_data);
			draw_data.pos_x++;
		}
	}
	return (touch_center);
}
