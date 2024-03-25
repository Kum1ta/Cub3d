/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/25 18:15:42 by psalame          ###   ########.fr       */
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

	raySpeed = 0.01f;
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
	char		*tmp;
	int			i;

	if (img)
		mlx_destroy_image(mlx->mlx, img);
	if (need_free)
		return ;
	img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	i = -1;
	// while (i < WIDTH)
	// {
	// 	angle[i] = (mlx->map->playerPos.h - FOV / 2) + (float)i / (float)WIDTH * FOV;
	// 	if (angle[i] < 0)
	// 		angle[i] += 360;
	// 	else if (angle[i] > 360)
	// 		angle[i] -= 360;
	// 	distance[i] = raycast(mlx, angle[i]);
	// 	//probleme avec raycast qui semble renvoyer de la merde. ensuite il faut faire les murs en fonction de la distance
	// 	// printf("angle:%f, dist: %f\n", angle[i], distance[i]);
	// 	i++;
	// }
	while (++i < WIDTH)
	{
		angle[i] = (mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV) - 90;
		if (angle[i] < 0)
			angle[i] += 360;
		else if (angle[i] > 360)
			angle[i] -= 360;
		distance[i] = raycast(mlx, angle[i]).dist;
		// if (distance[i] < 0.1)
		// 	distance[i] = 0.1;
		float wall_size = HEIGHT / distance[i];
		if (wall_size > HEIGHT)
			wall_size = HEIGHT - 1;
		int wall_start = (HEIGHT - wall_size) / 2;
		int wall_end = (HEIGHT + wall_size) / 2;
		int j = -1;
		while (++j < wall_start)
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xFF0000FF);
		}
		while (j < wall_end)
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xFFFF0000);
			j++;
		}
		while (j < HEIGHT)
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xFF00FF00);
			j++;
		}
		// float radian = angle[i] * (PI / 180.0f);
		// int end_x = WIDTH / 2 + (distance[i]) * sin(radian) * 10;
		// int end_y = HEIGHT / 2 + (distance[i]) * cos(radian) * 10;
		// draw_line(mlx, img, (int[4]){WIDTH / 2, HEIGHT / 2, end_x, end_y}, 0xFF00FF00);
	}
	// exit(0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	// item_effect(mlx);
	// put_actual_weapon(mlx, img);
	// mini_map(mlx, angle, distance, 0);
	// inventory(mlx, img, 0);
	// tmp = ft_strjoin_gnl(ft_itoa(mlx->player->ammo), " / 30");
	// mlx_string_put(mlx->mlx, mlx->win, WIDTH - 150, HEIGHT - 210, 0xFF00FF00, tmp);
	// free(tmp);
}

/*
			distance[i] = raycast(mlx, angle[i]);
		float radian = angle[i] * (PI / 180.0f);
		int end_x = WIDTH / 2 + (distance[i]) * sin(radian) * 10;
        int end_y = HEIGHT / 2 + (distance[i]) * cos(radian) * 10;
        
        draw_line(mlx, img, (int[4]){WIDTH / 2, HEIGHT / 2, end_x, end_y}, 0xFF00FF00);
*/

/*
	// for (int i = 0; i < WIDTH; i++)
	// {
	// 	angle[i] = mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV;
	// 	distance[i] = raycast(mlx, angle[i]);
	// 	// if (distance[i] < 0.1)
	// 	// 	distance[i] = 0.1;
	// 	int	wall_size = HEIGHT / distance[i];
	// 	if (wall_size > HEIGHT)
	// 		wall_size = HEIGHT - 1;
	// 	int wall_start = HEIGHT / 2 - wall_size / 2;
	// 	int wall_end = HEIGHT / 2 + wall_size / 2;
	// 	int color = 0xFFFF0000;
	// 	if (angle[i] > 0 && angle[i] < 3.14)
	// 		color = 0xFF00FF00;
	// 	for (int j = 0; j < wall_start; j++)
	// 		mlx_set_image_pixel(mlx->mlx, img, i, j, 0xE00000FF);
	// 	for (int j = wall_start; j < wall_end; j++)
	// 		mlx_set_image_pixel(mlx->mlx, img, i, j, color);
	// 	for (int j = wall_end; j < HEIGHT; j++)
	// 		mlx_set_image_pixel(mlx->mlx, img, i, j, 0xE000FF00);
	// 	draw_line(mlx, img, (int[4]){100, 100, sin(angle[i]) * 100 + distance[i], cos(angle[i]) * 100 + distance[i]}, 0xFF00FF00);
	// }
*/