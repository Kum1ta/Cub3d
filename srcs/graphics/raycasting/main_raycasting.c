/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 15:17:31 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

typedef struct s_calcul
{
	int	dx;
	int	dy;
	int	incre;
	int	incrne;
	int	d;
	int	x;
	int	y;
}	t_calcul;

void	draw_line_0(t_mlx *mlx, void *img, int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dx;
	c.incrne = 2 * (c.dy + c.dx);
	c.d = c.dx - c.dy;
	c.x = pos[0] - 1;
	c.y = pos[1] + 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.y > pos[3])
	{
		if (c.d <= 0)
		{
			c.d += c.incre;
			c.y--;
		}
		else
		{
			c.d += c.incrne;
			c.x++;
			c.y--;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_45(t_mlx *mlx, void *img, int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dy;
	c.incrne = 2 * (c.dy + c.dx);
	c.d = c.dx - c.dy;
	c.x = pos[0] - 1;
	c.y = pos[1] + 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.x < pos[2])
	{
		if (c.d <= 0)
		{
			c.d -= c.incre;
			c.x++;
		}
		else
		{
			c.d -= c.incrne;
			c.x++;
			c.y--;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_90(t_mlx *mlx, void *img, int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dy;
	c.incrne = 2 * (c.dx - c.dy);
	c.d = c.dy - c.dx;
	c.x = pos[0] - 1;
	c.y = pos[1];
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.x < pos[2])
	{
		if (c.d <= 0)
		{
			c.d += c.incre;
			c.x++;
		}
		else
		{
			c.d -= c.incrne;
			c.x++;
			c.y++;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_135(t_mlx *mlx, void *img, int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dx;
	c.incrne = 2 * (c.dx - c.dy);
	c.d = c.dx - c.dy;
	c.x = pos[0];
	c.y = pos[1] - 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.y < pos[3])
	{
		if (c.d <= 0)
			c.d += c.incre;
		else
		{
			c.d += c.incrne;
			c.x++;
		}
		c.y++;
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_180(t_mlx *mlx, void *img,  int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dx;
	c.incrne = 2 * (c.dy + c.dx);
	c.d = c.dx - c.dy;
	c.x = pos[0] + 1;
	c.y = pos[1] - 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.y < pos[3])
	{
		if (c.d >= 0)
		{
			c.d += c.incre;
			c.y++;
		}
		else
		{
			c.d += c.incrne;
			c.x--;
			c.y++;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_225(t_mlx *mlx, void *img,  int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dy;
	c.incrne = 2 * (c.dy + c.dx);
	c.d = c.dx - c.dy;
	c.x = pos[0] + 1;
	c.y = pos[1] - 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.x > pos[2])
	{
		if (c.d >= 0)
		{
			c.d -= c.incre;
			c.x--;
		}
		else
		{
			c.d -= c.incrne;
			c.x--;
			c.y++;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_270(t_mlx *mlx, void *img,  int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dy;
	c.incrne = 2 * (c.dy - c.dx);
	c.d = c.dx - c.dy;
	c.x = pos[0] + 1;
	c.y = pos[1];
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.x > pos[2])
	{
		if (c.d <= 0)
		{
			c.d -= c.incre;
			c.x--;
		}
		else
		{
			c.d -= c.incrne;
			c.x--;
			c.y--;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}

void	draw_line_315(t_mlx *mlx, void *img,  int pos[4], int color)
{
	t_calcul	c;

	c.dx = pos[2] - pos[0];
	c.dy = pos[3] - pos[1];
	c.incre = 2 * c.dx;
	c.incrne = 2 * (c.dx - c.dy);
	c.d = c.dy - c.dx;
	c.x = pos[0];
	c.y = pos[1] + 1;
	mlx_set_image_pixel(mlx->mlx, img, pos[0], pos[1], color);
	while (c.y > pos[3])
	{
		if (c.d <= 0)
		{
			c.d -= c.incre;
			c.y--;
		}
		else
		{
			c.d -= c.incrne;
			c.x--;
			c.y--;
		}
		mlx_set_image_pixel(mlx->mlx, img, c.x, c.y, color);
	}
}


void	draw_line(t_mlx *mlx, void *img, int pos[4], int color)
{
	double	angle;

	angle = atan2(pos[2] - pos[0], pos[3] - pos[1]) * (180.0 / PI);
	if (angle >= 135 && angle <= 180)
		draw_line_0(mlx, img, pos, color);
	else if (angle >= 90 && angle < 135)
		draw_line_45(mlx, img, pos, color);
	else if (angle >= 45 && angle < 90)
		draw_line_90(mlx, img, pos, color);
	else if (angle >= 0 && angle <= 45)
		draw_line_135(mlx, img, pos, color);
	else if (angle > -45 && angle < 0)
		draw_line_180(mlx, img, pos, color);
	else if (angle >= -90 && angle <= -45)
		draw_line_225(mlx, img, pos, color);
	else if (angle > -135 && angle <= -90)
		draw_line_270(mlx, img, pos, color);
	else if (angle > -180 && angle <= -135)
		draw_line_315(mlx, img, pos, color);
}

float raycast(t_mlx *mlx, float angle)
{
	float distance = 0.0;

	while (distance < MAX_DISTANCE)
	{
		float posX = mlx->map->playerPos.x + distance * cos(angle);
		float posY = mlx->map->playerPos.y + distance * sin(angle);
		int tileX = (int)(posX);
		int tileY = (int)(posY);
		if (mlx->map->blocks[tileX][tileY] == WALL)
		{
			float deltaX = posX - mlx->map->playerPos.x;
			float deltaY = posY - mlx->map->playerPos.y;
			printf("posX : %f, posY : %f, tileX : %d, tileY : %d\n", posX, posY, tileX, tileY);
			distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			break;
		}
		distance += 0.1;
	}
	return distance;
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
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->weapon_game->img, 0, 0);
	// else if (mlx->player->actual_weapon == FIST_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->fist_inv->img, 0, 0);
	// else if (mlx->player->actual_weapon == KNIFE_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->knife_inv->img, 0, 0);
}

void	play_sound(t_mlx *mlx)
{
	static int	i = 0;
	static long long last_time = 0;
	static bool	last = false;


	if (i == 0)
	{
		printf("\033[0;31mDon't forget to remove the function \"play_sound()\" : Forbidden fonction\n\033[0m");
		i++;
	}
	last = false;
	if (mlx->player->actual_weapon == WEAPON_INV && (mlx->mouse->pressed_left && (get_now_time() - last_time > 150000)))
	{
		system("paplay ./sounds/game/weapon_fire.wav &");
		last_time = get_now_time();
	}
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
	int			i;

	if (img)
		mlx_destroy_image(mlx->mlx, img);
	if (need_free)
		return ;
	img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	i = 0;
	printf("Real start angle  : %f\n", mlx->map->playerPos.h - FOV / 2 + 360);
	printf("Real end angle  : %f\n", mlx->map->playerPos.h + FOV / 2);
	printf("Joueur x : %f, y : %f\n", mlx->map->playerPos.x, mlx->map->playerPos.y);
	while (i < WIDTH)
	{
		angle[i] = (mlx->map->playerPos.h - FOV / 2) + (float)i / (float)WIDTH * FOV;
		if (angle[i] < 0)
			angle[i] += 360;
		else if (angle[i] > 360)
			angle[i] -= 360;
		distance[i] = raycast(mlx, angle[i]);
		int	wall_size = HEIGHT / distance[i];
		if (wall_size > HEIGHT)
			wall_size = HEIGHT - 1;
		int wall_start = HEIGHT / 2 - wall_size / 2;
		int wall_end = HEIGHT / 2 + wall_size / 2;
		int color = 0xFFFF0000;
		if (angle[i] > 0 && angle[i] < 3.14)
			color = 0xFF00FF00;
		for (int j = 0; j < wall_start; j++)
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xE00000FF);
		for (int j = wall_start; j < wall_end; j++)
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
		for (int j = wall_end; j < HEIGHT; j++)
			mlx_set_image_pixel(mlx->mlx, img, i, j, 0xE000FF00);
		//faire un trait qui represente la distance ainsi que l'angle
		draw_line(mlx, img, (int[4]){100, 100, sin(angle[i]) * 100 + distance[i], cos(angle[i]) * 100 + distance[i]}, 0xFF00FF00);
		i++;
	}
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
	// play_sound(mlx);
	// put_actual_weapon(mlx, img);
	// mini_map(mlx, angle, distance, 0);
	inventory(mlx, img, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	// exit(0);
}
