/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/29 21:06:31 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

void	calculate_ray_data(t_raydata *ray, float posX, float posY)
{
	if (posX - ((int) posX) < 0.02 || posX - ((int) posX) > 0.98)
	{
		if (posX - ((int) posX) < 0.02)
			ray->dir = 0;
		else
			ray->dir = 2;
		ray->imgXPercent = posY - ((int) posY);
	}
	else
	{
		if (posY - ((int) posY) > 0.98)
			ray->dir = 1;
		else
			ray->dir = 3;
		ray->imgXPercent = posX - ((int) posX);
	}
	ray->found = true;
}

t_raydata	*raycast(t_mlx *mlx, float angle)
{
	float 		posX;
	float		posY;
	int			tileX;
	int			tileY;
	float		raySpeed;
	float		rAngle;
	t_raydata	*res;

	res = malloc(sizeof(t_raydata));
	if (!res)
		return (NULL);
	raySpeed = 0.01f + (QUALITY * 0.01f);
	ft_bzero(res, sizeof(t_raydata));
	rAngle = angle * PI / 180;
	while (res->dist < MAX_DISTANCE)
	{
		posX = mlx->map->playerPos.x + (res->dist * cos(rAngle));
		posY = mlx->map->playerPos.y + (res->dist * sin(rAngle));
		tileX = (int)(posX);
		tileY = (int)(posY);

		if (tileX < 0 || tileX >= mlx->menu_map->width || tileY < 0 || tileY >= mlx->menu_map->height)
			break ;
		else if (mlx->map->blocks[tileY][tileX] == WALL)
		{
			calculate_ray_data(res, posX, posY);
			return (res);
		}
		res->dist += raySpeed;
	}
	res->dist = MAX_DISTANCE;
	return (res);
}

void	put_actual_weapon(t_mlx *mlx, void *img)
{
	int	i;

	i = -1;
	while (++i < 20)
		mlx_set_image_pixel(mlx->mlx, img, WIDTH / 2 - 10 + i, HEIGHT / 2, 0xFF00FF00);
	i = -1;
	while (++i < 20)
		mlx_set_image_pixel(mlx->mlx, img, WIDTH / 2, HEIGHT / 2 - 10 + i, 0xFF00FF00);
	if (mlx->player->actual_weapon == WEAPON_INV)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->textures->weapon_game->img,
			mlx->player->xy_item[0],
			mlx->player->xy_item[1]
		);
	// else if (mlx->player->actual_weapon == KNIFE_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->knife_inv->img, 0, 0);
}

void	weapon_effect(t_mlx *mlx, long long *last_time)
{
	if (!mlx->player->is_reloading && (mlx->mouse->pressed_left && (get_now_time() - *last_time > 150000)) && mlx->player->ammo)
	{
		system("paplay ./sounds/game/weapon_fire.wav &");
		*last_time = get_now_time();
		mlx->player->ammo--;
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->fire_gun->img, 938 + mlx->player->xy_item[0], 500 + mlx->player->xy_item[1]);
	}
	if (!mlx->player->is_reloading && mlx->keyboard->r && get_now_time() - *last_time > 50000 && mlx->player->ammo < 30)
	{
		system("paplay --volume=50000 ./sounds/game/weapon_reload.wav &");
		*last_time = get_now_time();
		mlx->player->is_reloading = true;
	}
	if (mlx->player->is_reloading)
	{
		mlx->player->xy_item[1] += 3;
		if (*last_time + 1700000 < get_now_time())
		{
			mlx->player->is_reloading = false;
			mlx->player->ammo = 30;
			mlx->player->xy_item[1] = 0;
		}
	}
}

void	item_effect(t_mlx *mlx)
{
	static int	i = 0;
	static long long last_time = 0;

	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"weapon_effect()\" : Forbidden fonction\n\033[0m");
		i++;
	}
	if (mlx->player->actual_weapon == WEAPON_INV)
		weapon_effect(mlx, &last_time);
	else if (mlx->player->actual_weapon == KNIFE_INV && mlx->mouse->pressed_left && get_now_time() - last_time > 500000)
	{
		system("paplay ./sounds/game/cut_hit.wav &");
		last_time = get_now_time();
	}
}

void	fill_background(t_mlx *mlx, void *img)
{
	int	color_ceiling;
	int	color_floor;
	int	i;
	int	j;

	i = -1;
	color_ceiling = 255 << 24 | mlx->map->texture.ceiling[0] << 16 | mlx->map->texture.ceiling[1] << 8 | mlx->map->texture.ceiling[2];
	color_floor = 255 << 24 | mlx->map->texture.floor[0] << 16 | mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT / 2)
			mlx_set_image_pixel(mlx->mlx, img, i, j, color_ceiling);
		while (j < HEIGHT)
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

void	free_ray(t_raydata **ray)
{
	int	i;

	i = -1;
	while (++i < WIDTH)
		free(ray[i]);
}

void	correct_fish_eye(t_raydata *ray, float angle_ray, t_mlx *mlx)
{
	float	radian;
	float	ra;


	ra = angle_ray + 90;
	ajust_angle(&ra);
	radian = (mlx->map->playerPos.h - ra) * (PI / 180.0f);
	ray->dist *= cos(radian);
}

void	calcul_wall_size(t_raydata *ray)
{
	int	tmp;

	if (ray->dist < 0.2)
		ray->dist = 0.2;
	ray->wall_size = (HEIGHT / ray->dist) * 1.0;
	tmp = ray->wall_size;
	if (ray->wall_size > HEIGHT)
		ray->wall_size = HEIGHT - 1;
	ray->wall_start = (HEIGHT - ray->wall_size) / 2;
	ray->wall_end = (HEIGHT + ray->wall_size) / 2;
	ray->diff = tmp - ray->wall_size;
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

void	show_fps(t_mlx *mlx)
{
	int	x;
	int	y;

	if (SHOW_FPS)
	{
		y = 0;
		while (y < 20)
		{
			x = 0;
			while (x < 40)
			{
				mlx_pixel_put(mlx->mlx, mlx->win,  WIDTH - x, y, 0x00000000);
				x++;
			}
			y++;
		}
		put_fps(mlx, 0);
	}
}

int	choose_anti_aliasing(int distance)
{
	int	lvl;

	if (ANTIALIASING_LEVEL == 2)
	{
		if (distance < 2)
			lvl = 1;
		else
			lvl = 2;
	}
	else if (distance < 2)
		lvl = 1;
	else if (distance < 5)
		lvl = ANTIALIASING_LEVEL / 4;
	else if (distance < 10)
		lvl = ANTIALIASING_LEVEL / 2;
	else
		lvl = ANTIALIASING_LEVEL;
	return (lvl);
}

int	get_supersampling_color(t_mlx *mlx, int x, int y, int distance)
{
	int		color[3];
	int		x_pos;
	int		y_pos;
	int		color_tmp;
	int		lvl;
	
	if (ANTIALIASING_LEVEL == 1)
		return (mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img, x, y));
	lvl = choose_anti_aliasing(distance);
	ft_bzero(color, 3 * sizeof(int));
	y_pos = -1;
	while (++y_pos < lvl)
	{
		x_pos = -1;
		while (++x_pos < lvl)
		{
			color_tmp = mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img,
				x + x_pos, y + y_pos);
			color[0] += (color_tmp & 0x00FF0000) >> 16;
			color[2] += (color_tmp & 0x0000FF00) >> 8;
			color[1] += color_tmp & 0x000000FF;
		}
	}
	return (255 << 24 | (color[0] / (lvl * lvl)) << 16
		| (color[2] / (lvl * lvl)) << 8 | (color[1] / (lvl * lvl)));
}

void	downscalling(t_raydata *ray, t_mlx *mlx, int i, float factor)
{
	float	tmp;
	int		color;
	int		last;
	int		j;

	last = 0;
	j = ray->wall_start - 1;
	while (++j < ray->wall_end)
	{
		tmp = last + factor;
		while (last < tmp)
		{
			if (ray->dir == 0)
				mlx->tmp = mlx->textures->north;
			else if (ray->dir == 1)
				mlx->tmp = mlx->textures->east;
			else if (ray->dir == 2)
				mlx->tmp = mlx->textures->south;
			else
				mlx->tmp = mlx->textures->west;
			color = get_supersampling_color(mlx, (int)(ray->imgXPercent
				* ((t_img *)mlx->tmp)->width), (int)(last
				* ((t_img *)mlx->tmp)->height / ray->wall_size),
				(int)ray->dist);
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
			last++;
		}
	}
}

void	upscalling(t_raydata *ray, t_mlx *mlx, int i, float factor)
{
	int		color;
	int		j;

	(void)factor;
	j = ray->wall_start;
	while (j < ray->wall_end)
	{
		if (ray->dir == 0)
			mlx->tmp = mlx->textures->north;
		else if (ray->dir == 1)
			mlx->tmp = mlx->textures->east;
		else if (ray->dir == 2)
			mlx->tmp = mlx->textures->south;
		else
			mlx->tmp = mlx->textures->west;
		color = get_supersampling_color(mlx, (int)(ray->imgXPercent
			* ((t_img *)mlx->tmp)->width), (int)((j - ray->wall_start)
			* ((t_img *)mlx->tmp)->height / ray->wall_size), (int)ray->dist);
		mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
		j++;
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	t_raydata	*ray[WIDTH];
	float		angle[WIDTH];
	int			i;
	float		factor;

	if (need_free)
		return ;
	i = -1;
	while (++i < WIDTH)
	{
		angle[i] = (mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV) - 90;
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
	i = -1;
	while (++i < WIDTH)
	{
		put_celling_floor(mlx, ray[i], i);
		if (ray[i]->dir == 0)
			factor = (float)ray[i]->wall_size / (float)mlx->textures->north->height;
		else if (ray[i]->dir == 1)
			factor = (float)ray[i]->wall_size / (float)mlx->textures->east->height;
		else if (ray[i]->dir == 2)
			factor = (float)ray[i]->wall_size / (float)mlx->textures->south->height;
		else
			factor = (float)ray[i]->wall_size / (float)mlx->textures->west->height;
		if (factor < 1)
			downscalling(ray[i], mlx, i, factor);
		else
			upscalling(ray[i], mlx, i, factor);
	}
	show_fps(mlx);
	// item_effect(mlx);
	// put_actual_weapon(mlx, img);
	// mini_map(mlx, angle, distance, 0);
	// inventory(mlx, img, 0);
	// tmp = ft_strjoin_gnl(ft_itoa(mlx->player->ammo), " / 30");
	// mlx_string_put(mlx->mlx, mlx->win, WIDTH - 150, HEIGHT - 210, 0xFF00FF00, tmp);
	// free(tmp);
}



// FONCTION POUR AFFICHER LE POINT D'ARRIVEE DES RAYONS
		// float radiand = angle[i] * (PI / 180.0f);
		// int end_x = WIDTH / 4 + ({VALEUR DISTANCE}) * sin(radiand) * 10;
		// int end_y = HEIGHT / 2 + (tmp) * cos(radiand) * 10;
		// if (end_x >= 0 && end_x < WIDTH && end_y >= 0 && end_y < HEIGHT)
		// {
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y + 1, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y + 1, 0xFF00FF00);