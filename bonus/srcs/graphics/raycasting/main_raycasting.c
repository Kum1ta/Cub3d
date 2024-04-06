/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/06 20:46:29 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

typedef struct s_ray {
	float	rAngle;
	float	dirX;
	float	dirY;
	int		posX;
	int		posY;
	float	distX;
	float	distY;
	float	deltaDistX;
	float	deltaDistY;
	int		stepX;
	int		stepY;
	int		nbStep;
	int		dir;
}	t_ray;

void	init_ray(t_ray *ray, t_mlx *mlx, float angle, int screenX)
{
	ray->rAngle = angle * PI / 180;
	ray->dirX = cos(ray->rAngle);
	ray->dirY = sin(ray->rAngle);
	ray->posX = (int) mlx->map->playerPos.x;
	ray->posY = (int) mlx->map->playerPos.y;
	ray->deltaDistX = sqrt(1 + (ray->dirY * ray->dirY) / (ray->dirX * ray->dirX));
	ray->deltaDistY = sqrt(1 + (ray->dirX * ray->dirX) / (ray->dirY * ray->dirY));
	if (ray->dirX < 0)
		ray->distX = (mlx->map->playerPos.x - ray->posX) * ray->deltaDistX;
	else
		ray->distX = (ray->posX + 1 - mlx->map->playerPos.x) * ray->deltaDistX;
	if (ray->dirY < 0)
		ray->distY = (mlx->map->playerPos.y - ray->posY) * ray->deltaDistY;
	else
		ray->distY = (ray->posY + 1 - mlx->map->playerPos.y) * ray->deltaDistY;
	ray->stepX = 1 - 2 * (ray->dirX < 0);
	ray->stepY = 1 - 2 * (ray->dirY < 0);
	ray->nbStep = 0;
}

// todo send back more informations :
//   wall bigger behind -> multisize walls
t_raydata	*raycast(t_mlx *mlx, float angle, int screenX, int size)
{
	t_raydata	*res;
	t_ray		ray;

	res = ft_calloc(1, sizeof(t_raydata));
	if (!res)
		return (NULL);
	init_ray(&ray, mlx, angle, screenX);
	while (!res->found && ray.nbStep < MAX_DISTANCE)
	{
		if (ray.distX < ray.distY)
		{
			ray.distX += ray.deltaDistX;
			ray.posX += ray.stepX;
			ray.dir = 0;
		}
		else
		{
			ray.distY += ray.deltaDistY;
			ray.posY += ray.stepY;
			ray.dir = 1;
		}
		if (ray.posX >= 0 && ray.posY >= 0 && ray.posX < mlx->map->width && ray.posY < mlx->map->height)
		{
			res->block = &(mlx->map->blocks[ray.posY][ray.posX]);
			if ((res->block->type == WALL && res->block->data.wall > size) || (res->block->type == DOOR && res->block->data.door == false)) // ici pour la detection de la hauteur du mur
			{
				res->found = true;
				if (ray.dir == 0)
				{
					res->dist = ray.distX - ray.deltaDistX;
					res->dir = ray.dir + 2 * (ray.stepX == -1);
					res->imgXPercent = mlx->map->playerPos.y + res->dist * ray.dirY;
				}
				else
				{
					res->dist = ray.distY - ray.deltaDistY;
					res->dir = ray.dir + 2 * (ray.stepY == -1);
					res->imgXPercent = mlx->map->playerPos.x + res->dist * ray.dirX;
				}
				res->imgXPercent = res->imgXPercent - ((int) res->imgXPercent);
			}
		}
		ray.nbStep++;
	}
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
	if (!mlx->player->is_reloading && is_key_down(mlx->keyboard, KEY_R) && get_now_time() - *last_time > 50000 && mlx->player->ammo < 30)
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

void	free_ray(t_raydata ***ray)
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

void	calcul_wall_size(t_mlx *mlx, t_raydata *ray)
{
	int	tmp;

	if (!ray->found)
	{
		ray->wall_size = 0;
		ray->wall_start = HEIGHT / 2;
		ray->wall_end = HEIGHT / 2;
		return ;
	}
	ray->wall_size = (HEIGHT / ray->dist);
	if (ray->wall_size > HEIGHT)
		ray->wall_size = HEIGHT;
	ray->wall_start = (HEIGHT - ray->wall_size) / 2;
	ray->wall_end = (HEIGHT + ray->wall_size) / 2;
	if (ray->block->type == WALL)
		ray->wall_start = ray->wall_start - ((ray->wall_end - ray->wall_start) * (ray->block->data.wall - 1));
	else
		ray->wall_start = ray->wall_start - ((ray->wall_end - ray->wall_start) * (WALL_SIZE - 1));
	ray->wall_start = ray->wall_start - ((ray->wall_end - ray->wall_start) * (WALL_SIZE - 1));
}

void	put_celling_floor(t_mlx *mlx, t_raydata *ray, int i)
{
	int		j;
	int		k;
	int		color;

	k = -1;
	while (++k < QUALITY)
	{
		j = -mlx->map->playerPos.v;
		while (j < ray->wall_start)
		{
			color = 255 << 24 | mlx->map->texture.ceiling[0] << 16
			| mlx->map->texture.ceiling[1] << 8
			| mlx->map->texture.ceiling[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->playerPos.v, color);
			j++;
		}
		j += ray->wall_size;
		while (j < HEIGHT - mlx->map->playerPos.v)
		{
			color = 255 << 24 | mlx->map->texture.floor[0] << 16
			| mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->playerPos.v, color);
			j++;
		}
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
			while (x < 60)
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

	k = -1;
	if (ray->dir == 0)
		mlx->tmp = mlx->textures->north;
	else if (ray->dir == 1)
		mlx->tmp = mlx->textures->east;
	else if (ray->dir == 2)
		mlx->tmp = mlx->textures->south;
	else
		mlx->tmp = mlx->textures->west;
	imgX = ray->imgXPercent * ((t_img *)mlx->tmp)->width;
	wall_size = HEIGHT / ray->dist;
	while (++k < QUALITY)
	{
		j = ray->wall_start - 1;
		imgY = ((j + 1) - (HEIGHT - wall_size) / 2) * factor;
		while (++j < ray->wall_end)
		{
			imgY += factor;
			color = get_ss_color(mlx, (int) imgX, (int) imgY, (int)ray->dist);
			if (color == 0)
			{
				imgY = 0;
				color = get_ss_color(mlx, (int) imgX, (int) imgY, (int)ray->dist);
			}
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->playerPos.v, color);
		}
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	t_raydata	*ray[WIDTH][MAX_HEIGHT];
	float		angle;
	int			i;
	int			j;
	float		factor;

	if (need_free)
		return ;
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < MAX_HEIGHT)
		{
			if (i % QUALITY == 0)
			{
				angle = (mlx->map->playerPos.h - FOV / 2 + (float)i / (float)WIDTH * FOV) - 90;
				ajust_angle(&angle);
				ray[i][j] = raycast(mlx, angle, i, j);
				if (i == WIDTH / 2)
					mlx->player->front_ray = *(ray[i][j]);
				if (!ray[i])
				{
					// free_ray(ray);
					return ;
				}
				correct_fish_eye(ray[i][j], angle, mlx);
				calcul_wall_size(mlx, ray[i][j]);
			}
		}
	}
	i = 0;
	while (i < WIDTH)
	{
		put_celling_floor(mlx, ray[i][j], i);
		j = MAX_HEIGHT - 1;
		while (j >= 0)
		{
			if (ray[i][j]->found)
			{
				factor = HEIGHT / ray[i][j]->dist;
				if (ray[i][j]->dir == 0)
					factor = (float)mlx->textures->north->height / factor;
				else if (ray[i][j]->dir == 1)
					factor = (float)mlx->textures->east->height / factor;
				else if (ray[i][j]->dir == 2)
					factor = (float)mlx->textures->south->height / factor;
				else
					factor = (float)mlx->textures->west->height / factor;
				scalling(ray[i][j], mlx, i, factor, j);
			}
			j--;
		}
		i += QUALITY;
	}
	show_fps(mlx);
	// item_effect(mlx);
	// put_actual_weapon(mlx, img);
	mini_map(mlx);
	// inventory(mlx, img, 0);
	// tmp = ft_strjoin_gnl(ft_itoa(mlx->player->ammo), " / 30");
	// mlx_string_put(mlx->mlx, mlx->win, WIDTH - 150, HEIGHT - 210, 0xFF00FF00, tmp);
	// free(tmp);
}
