/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/28 21:40:04 by edbernar         ###   ########.fr       */
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

t_raydata	raycast(t_mlx *mlx, float angle)
{
	float		raySpeed;
	float		rAngle;
	t_raydata	res;

	raySpeed = 0.02f;
	ft_bzero(&res, sizeof(t_raydata));
	rAngle = angle * PI / 180;
	while (res.dist < MAX_DISTANCE)
	{
		float posX = mlx->map->playerPos.x + (res.dist * cos(rAngle));
		float posY = mlx->map->playerPos.y + (res.dist * sin(rAngle));
		int tileX = (int)(posX);
		int tileY = (int)(posY);

		if (tileX < 0 || tileX >= mlx->menu_map->width || tileY < 0 || tileY >= mlx->menu_map->height)
			break ;
		else if (mlx->map->blocks[tileY][tileX] == WALL)
		{
			calculate_ray_data(&res, posX, posY);
			return res;
		}
		res.dist += raySpeed;
	}
	res.dist = MAX_DISTANCE;
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
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->weapon_game->img, mlx->player->xy_item[0], mlx->player->xy_item[1]);
	// else if (mlx->player->actual_weapon == FIST_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->fist_inv->img, 0, 0);
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
	// else if (mlx->player->actual_weapon == FIST_INV)
	// 	system("afplay ./sounds/fist.wav &");
	else if (mlx->player->actual_weapon == KNIFE_INV && mlx->mouse->pressed_left && get_now_time() - last_time > 500000)
	{
		system("paplay ./sounds/game/cut_hit.wav &");
		last_time = get_now_time();
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	float		angle[WIDTH];
	float		distance[WIDTH];
	static void	*img = NULL;
	int			color; 
	char		*tmp;
	int			i;

	if (img && need_free)
	{
		mlx_destroy_image(mlx->mlx, img);
		return ;
	}
	if (!img)
		img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	i = -1;
	int l = 0;
	int	wall_size = 0;
	int wall_start = 0;
	int wall_end = 0;
	while (++i < WIDTH)
	{
		if (l == 0)
		{
			angle[i] = (mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV) - 90;
			if (angle[i] < 0)
				angle[i] += 360;
			else if (angle[i] > 360)
				angle[i] -= 360;
			distance[i] = raycast(mlx, angle[i]).dist;
			float ra = angle[i] + 90;
			if (ra > 360)
				ra -= 360;
			if (ra < 0)
				ra += 360;
			float radian = (mlx->map->playerPos.h - ra) * (PI / 180.0f);
			float tmp = distance[i];
			distance[i] *= cos(radian);
			if (distance[i] < 0.2)
				distance[i] = 0.2;
			wall_size = (HEIGHT / distance[i]) * 1.5;
			if (wall_size > HEIGHT)
				wall_size = HEIGHT - 1;
			wall_start = (HEIGHT - wall_size) / 2;
			wall_end = (HEIGHT + wall_size) / 2;
		}
		int j = -1;
		while (++j < wall_start)
		{
			color = 255 << 24 | mlx->map->texture.ceiling[0] << 16 | mlx->map->texture.ceiling[1] << 8 | mlx->map->texture.ceiling[2]; 
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xFF0000FF);
		}
		int	k = 0;
		while (j < wall_end)
		{
			// color = mlx_get_image_pixel(mlx->mlx, mlx->textures->north->img, i, k);
			// 0xFF5A9FED = 255 << 24 | 90 << 16 | 159 << 8 | 237
			int a = 90 - distance[i] * 3;
			if (a < 0)
				a = 0;
			int b = 159 - distance[i] * 3;
			if (b < 0)
				b = 0;
			int c = 237 - distance[i] * 3;
			if (c < 0)
				c = 0;
			color = 255 << 24 | a << 16 | b << 8 | c;
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			k++;
			j++;
		}
		while (j < HEIGHT)
		{
			color = 255 << 24 | mlx->map->texture.floor[0] << 16 | mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2]; 
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			j++;
		}
		if (l == PRECISION)
			l = 0;
		else
			l++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	// item_effect(mlx);
	// put_actual_weapon(mlx, img);
	// mini_map(mlx, angle, distance, 0);
	// inventory(mlx, img, 0);
	// tmp = ft_strjoin_gnl(ft_itoa(mlx->player->ammo), " / 30");
	// mlx_string_put(mlx->mlx, mlx->win, WIDTH - 150, HEIGHT - 210, 0xFF00FF00, tmp);
	// free(tmp);
}



// FONCTION POUR AFFICHER LE POINT D'ARRIVEE DES RAYONS
		// SANS CORRECTION DE FISHEYE
		// float radiand = angle[i] * (PI / 180.0f);
		// int end_x = WIDTH / 4 + (tmp) * sin(radiand) * 10;
		// int end_y = HEIGHT / 2 + (tmp) * cos(radiand) * 10;
		// if (end_x >= 0 && end_x < WIDTH && end_y >= 0 && end_y < HEIGHT)
		// {
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y + 1, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y + 1, 0xFF00FF00);

		// }

		// AVEC CORRECTION DE FISHEYE
		// end_x = ((WIDTH / 4) * 3) + (distance[i]) * sin(radiand) * 10;
		// end_y = HEIGHT / 2 + (distance[i]) * cos(radiand) * 10;
		// if (end_x >= 0 && end_x < WIDTH && end_y >= 0 && end_y < HEIGHT)
		// {
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x, end_y + 1, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y, 0xFF00FF00);
		// 	mlx_pixel_put(mlx->mlx, mlx->win, end_x + 1, end_y + 1, 0xFF00FF00);

		// }