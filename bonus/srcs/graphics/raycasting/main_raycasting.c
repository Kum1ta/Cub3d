/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 18:10:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	fill_background(t_mlx *mlx, void *img)
{
	int	color_ceiling;
	int	color_floor;
	int	i;
	int	j;

	i = -1;
	color_ceiling = 255 << 24 | mlx->map->texture.ceiling[0] << 16 | mlx->map->texture.ceiling[1] << 8 | mlx->map->texture.ceiling[2];
	color_floor = 255 << 24 | mlx->map->texture.floor[0] << 16 | mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
	while (++i < mlx->stg->width)
	{
		j = -1;
		while (++j < mlx->stg->height / 2)
			mlx_set_image_pixel(mlx->mlx, img, i, j, color_ceiling);
		while (j < mlx->stg->height)
			mlx_set_image_pixel(mlx->mlx, img, i, j++, color_floor);
	}
}

void	ajust_angle(float *angle)
{
	if (*angle < 0)
		*angle += 360;
	else if (*angle > 360)
		*angle -= 360;
}

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
			ray[i].wall_start = ray[i].wall_start - ((ray[i].wall_end - ray[i].wall_start) * (ray[i].block->data.wall - 1));
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
		j = -mlx->map->cam_dir.z;
		while (j < ray->wall_start)
		{
			color = 255 << 24 | mlx->map->texture.ceiling[0] << 16
			| mlx->map->texture.ceiling[1] << 8
			| mlx->map->texture.ceiling[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->cam_dir.z, color);
			j++;
		}
		j += ray->wall_size - 1;
		while (++j < mlx->stg->height - mlx->map->cam_dir.z)
		{
			color = 255 << 24 | mlx->map->texture.floor[0] << 16
			| mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->cam_dir.z, color);
		}
	}
}

int	choose_anti_aliasing(t_mlx *mlx, int distance)
{
	int	lvl;

	if (mlx->stg->antialiasing == 2)
	{
		if (distance < 2)
			lvl = 1;
		else
			lvl = 2;
	}
	else if (distance < 2)
		lvl = 1;
	else if (distance < 5)
		lvl = mlx->stg->antialiasing / 4;
	else if (distance < 10)
		lvl = mlx->stg->antialiasing / 2;
	else
		lvl = mlx->stg->antialiasing;
	return (lvl);
}

static inline int	max(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

int	get_ss_color(t_mlx *mlx, int x, int y, int distance)
{
	int		color[3];
	int		x_pos;
	int		y_pos;
	int		color_tmp;
	int		lvl;
	
	if (mlx->no_texture_mod)
		return (0xFFAA0011);
	if (mlx->stg->antialiasing == 1)
		return (mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img, x, y));
	lvl = choose_anti_aliasing(mlx, distance);
	ft_bzero(color, 3 * sizeof(int));
	y_pos = -1;
	while (++y_pos < lvl)
	{
		x_pos = -1;
		while (++x_pos < lvl)
		{
			color_tmp = mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img,
				max(x + x_pos, ((t_img *)mlx->tmp)->width), max(y + y_pos, ((t_img *)mlx->tmp)->height));
			color[0] += (color_tmp & 0x00FF0000) >> 16;
			color[2] += (color_tmp & 0x0000FF00) >> 8;
			color[1] += color_tmp & 0x000000FF;
		}
	}
	return (255 << 24 | (color[0] / (lvl * lvl)) << 16
		| (color[2] / (lvl * lvl)) << 8 | (color[1] / (lvl * lvl)));
}

void	scalling(t_raydata *ray, t_mlx *mlx, int i, float factor, int size)
{
	int		j;
	int		k;
	float	wall_size;
	int		imgX;
	float	imgY;
	int		color;
	int		a_min, b_min, c_min;
	int		a, b, c;

	k = -1;
	if (ray->block->type == DOOR)
		mlx->tmp = &mlx->textures->door;
	else if (ray->dir == 0)
		mlx->tmp = &mlx->textures->north;
	else if (ray->dir == 1)
		mlx->tmp = &mlx->textures->east;
	else if (ray->dir == 2)
		mlx->tmp = &mlx->textures->south;
	else
		mlx->tmp = &mlx->textures->west;
	imgX = ray->imgXPercent * ((t_img *)mlx->tmp)->width;
	wall_size = mlx->stg->height / ray->dist;
	while (++k < mlx->stg->quality)
	{
		j = ray->wall_start - 1;
		if (j + mlx->map->cam_dir.z < 0)
			j = 0 - mlx->map->cam_dir.z - 1;
		imgY = ((j + 1) - (mlx->stg->height - ray->wall_size) / 2) * factor;
		while (imgY < 0)
			imgY += ((t_img *)mlx->tmp)->height;
		while (++j < fmin(ray->wall_end, mlx->stg->height - mlx->map->cam_dir.z))
		{
			imgY += factor;
			color = get_ss_color(mlx, (int) imgX, ((int) imgY) % ((t_img *)mlx->tmp)->height, (int)ray->dist);
			a_min = ((color & 0x00FF0000) >> 16) - 60;
            if (a_min < 0)
                a_min = 0;
            b_min = ((color & 0x0000FF00) >> 8) - 60;
            if (b_min < 0)
                b_min = 0;
            c_min = (color & 0x000000FF) - 60;
            if (c_min < 0)
                c_min = 0;
            a = ((color & 0x00FF0000) >> 16) - ray->dist * 5;
            if (a < a_min)
                a = a_min;
            b = ((color & 0x0000FF00) >> 8) - ray->dist * 5;
            if (b < b_min)
                b = b_min;
            c = (color & 0x000000FF)- ray->dist * 5;
            if (c < c_min)
                c = c_min;
            color = 255 << 24 | a << 16 | b << 8 | c;
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->cam_dir.z, color);
		}
	}
}

void	put_ammo(t_mlx *mlx)
{
	static char	str[] = "00 / 30";

	if (mlx->player->actual_weapon != WEAPON_INV)
		return ;
	str[0] = mlx->player->ammo / 10 + '0';
	str[1] = mlx->player->ammo % 10 + '0';
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 20.0f);
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 150, mlx->stg->height - 210, 0xFF00FF00, str);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
}

void	raycasting(t_mlx *mlx, int need_free)
{
	static t_raydata	**ray;
	int					i;
	int					j;
	float				factor;
	t_sprite			center_sprite;

	if (need_free)
		free(ray);
	if (need_free)
		return ;
	while (!ray)
		ray = malloc(mlx->stg->width * sizeof(t_raydata *));
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
				{
					factor = mlx->stg->height / ray[i][j].dist;
					if (ray[i][j].block->type == DOOR)
						factor = (float)mlx->textures->door.height / factor;
					else if (ray[i][j].dir == 0)
						factor = (float)mlx->textures->north.height / factor;
					else if (ray[i][j].dir == 1)
						factor = (float)mlx->textures->east.height / factor;
					else if (ray[i][j].dir == 2)
						factor = (float)mlx->textures->south.height / factor;
					else
						factor = (float)mlx->textures->west.height / factor;
					scalling(ray[i] + j, mlx, i, factor, j);
				}
				j--;
			}
		}
	}
	center_sprite = draw_sprites(mlx, ray);
	put_fps(mlx, 0);
	item_effect(mlx, center_sprite);
	put_actual_item(mlx);
	if (mlx->stg->show_minimap)
		mini_map(mlx);
	inventory(mlx, 0);
	put_ammo(mlx);
	show_popup(mlx);
	i = -1;
	while (++i < mlx->stg->width)
	{
		if (i % mlx->stg->quality == 0)
			free(ray[i]);
	}
}
