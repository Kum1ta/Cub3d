/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:56:57 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 20:14:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./raycasting.h"

typedef struct s_ray {
	int		posX;
	int		posY;
	float	dirX;
	float	dirY;
	t_vec2	dist;
	t_vec2	deltaDist;
	int		stepX;
	int		stepY;
	int		nbStep;
	int		dir;
}	t_ray;

void	init_ray(t_ray *ray, t_mlx *mlx, int screen_x, t_vec3 start)
{
	float	camX;

	camX = 2 * screen_x / (float) mlx->stg->width - 1;
	ray->dirX = mlx->map->camDir.x + mlx->map->camPlane.x * camX;
	ray->dirY = mlx->map->camDir.y + mlx->map->camPlane.y * camX;
	ray->posX = (int) start.x;
	ray->posY = (int) start.y;
	ray->deltaDist.x = fabs(1 / ray->dirX);
	ray->deltaDist.y = fabs(1 / ray->dirY);
	if (ray->dirX < 0)
		ray->dist.x = (start.x - ray->posX) * ray->deltaDist.x;
	else
		ray->dist.x = (ray->posX + 1 - start.x) * ray->deltaDist.x;
	if (ray->dirY < 0)
		ray->dist.y = (start.y - ray->posY) * ray->deltaDist.y;
	else
		ray->dist.y = (ray->posY + 1 - start.y) * ray->deltaDist.y;
	ray->stepX = 1 - 2 * (ray->dirX < 0);
	ray->stepY = 1 - 2 * (ray->dirY < 0);
	ray->nbStep = 0;
}

t_raydata	*raycast(t_mlx *mlx, int screen_x, bool catch_interract, t_vec3 start)
{
	t_raydata	*res;
	t_ray		ray;
	int			i;
	int			curr_size;
	int			max_height;

	max_height = MAX_HEIGHT;
	if (catch_interract)
		max_height = 1;
	res = ft_calloc(max_height, sizeof(t_raydata));
	if (!res)
		return (NULL);
	i = 0;
	init_ray(&ray, mlx, screen_x, start);
	curr_size = 0;
	while (curr_size < max_height && ray.nbStep < MAX_DISTANCE)
	{
		if (ray.dist.x < ray.dist.y)
		{
			ray.dist.x += ray.deltaDist.x;
			ray.posX += ray.stepX;
			ray.dir = 0;
		}
		else
		{
			ray.dist.y += ray.deltaDist.y;
			ray.posY += ray.stepY;
			ray.dir = 1;
		}
		if (ray.posX >= 0 && ray.posY >= 0 && ray.posX < mlx->map->width && ray.posY < mlx->map->height)
		{
			res[i].block = &(mlx->map->blocks[ray.posY][ray.posX]);
			if ((res[i].block->type == WALL && res[i].block->data.wall > curr_size) 
				|| (res[i].block->type == DOOR && (res[i].block->data.door == false || catch_interract) && curr_size == 0))
			{
				res[i].found = true;
				res[i].pos.x = ray.posX;
				res[i].pos.y = ray.posY;
				if (ray.dir == 0)
				{
					res[i].dist = ray.dist.x - ray.deltaDist.x;
					res[i].dir = ray.dir + 2 * (ray.stepX == -1);
					res[i].imgXPercent = start.y + res[i].dist * ray.dirY;
				}
				else
				{
					res[i].dist = ray.dist.y - ray.deltaDist.y;
					res[i].dir = ray.dir + 2 * (ray.stepY == -1);
					res[i].imgXPercent = start.x + res[i].dist * ray.dirX;
				}
				res[i].imgXPercent = res[i].imgXPercent - ((int) res[i].imgXPercent);
				curr_size++;
				if (res[i].block->type == WALL)
					curr_size = res[i].block->data.wall;
				i++;
			}
		}
		ray.nbStep++;
	}
	return (res);
}

void	put_actual_weapon(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 20)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 10 + i, mlx->stg->height / 2, 0xFF00FF00);
	i = -1;
	while (++i < 20)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->stg->width / 2, mlx->stg->height / 2 - 10 + i, 0xFF00FF00);
	if (mlx->player->actual_weapon == WEAPON_INV)
		draw_image_to_window(mlx, &mlx->textures->weapon_game,
			mlx->player->xy_item,
			(int [2]){mlx->stg->width, mlx->stg->height}
		);
	// else if (mlx->player->actual_weapon == KNIFE_INV)
	// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->knife_inv->img, 0, 0);
}

void	weapon_effect(t_mlx *mlx, long long *last_time, t_sprite center_sprite)
{
	int	player_touch;

	if (!mlx->player->is_reloading && (mlx->mouse->pressed_left && (get_now_time() - *last_time > 150000)) && mlx->player->ammo)
	{
		player_touch = -1;
		system("paplay --volume=65535 ./sounds/game/weapon_fire.wav &");
		*last_time = get_now_time();
		mlx->player->ammo--;
		draw_image_to_window(mlx, &mlx->textures->fire_gun,
			(int [2]){mlx->stg->width * 0.58 - 150 / 2, mlx->stg->height * 0.55 - 150 / 2},
			(int [2]){150, 150});
		if (mlx->game_server.status == CONNECTED)
		{
			player_touch = -1;
			if (center_sprite.type == SPRT_PLAYER)
				player_touch = center_sprite.data.player->serverId;
			if (player_touch != -1)
				system("paplay --volume=30000 ./sounds/game/hit.wav &");
			dprintf(mlx->game_server.sockfd, "shoot:%d,%.2f,%.2f,%.2f;", player_touch, mlx->map->playerPos.x, mlx->map->playerPos.y, mlx->map->playerPos.z);
		}
		mlx->player->xy_item[0] = 10;
		mlx->player->xy_item[1] = 10;
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
	else
	{
		if (mlx->player->xy_item[0] > 0)
			mlx->player->xy_item[0] -= 2;
		if (mlx->player->xy_item[1] > 0)
			mlx->player->xy_item[1] -= 2;
	}
}

void	item_effect(t_mlx *mlx, t_sprite center_sprite)
{
	static long long	last_time = 0;
	int					player_touch;

	if (mlx->player->actual_weapon == WEAPON_INV)
		weapon_effect(mlx, &last_time, center_sprite);
	else if (mlx->player->actual_weapon == KNIFE_INV && mlx->mouse->pressed_left && get_now_time() - last_time > 500000)
	{
		system("paplay --volume=65535 ./sounds/game/cut_hit.wav &");
		last_time = get_now_time();
		if (mlx->game_server.status == CONNECTED)
		{
			player_touch = -1;
			if (center_sprite.type == SPRT_PLAYER && center_sprite.dist < 2)
				player_touch = center_sprite.data.player->serverId;
			if (player_touch != -1)
				system("paplay --volume=30000 ./sounds/game/hit.wav &");
			dprintf(mlx->game_server.sockfd, "cut:%d,%.2f,%.2f,%.2f;", player_touch, mlx->map->playerPos.x, mlx->map->playerPos.y, mlx->map->playerPos.z);
		}
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
		j = -mlx->map->camDir.z;
		while (j < ray->wall_start)
		{
			color = 255 << 24 | mlx->map->texture.ceiling[0] << 16
			| mlx->map->texture.ceiling[1] << 8
			| mlx->map->texture.ceiling[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->camDir.z, color);
			j++;
		}
		j += ray->wall_size - 1;
		while (++j < mlx->stg->height - mlx->map->camDir.z)
		{
			color = 255 << 24 | mlx->map->texture.floor[0] << 16
			| mlx->map->texture.floor[1] << 8 | mlx->map->texture.floor[2];
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->camDir.z, color);
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
	if (ray->dir == 0)
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
		if (j + mlx->map->camDir.z < 0)
			j = 0 - mlx->map->camDir.z - 1;
		imgY = ((j + 1) - (mlx->stg->height - ray->wall_size) / 2) * factor;
		while (imgY < 0)
			imgY += ((t_img *)mlx->tmp)->height;
		while (++j < fmin(ray->wall_end, mlx->stg->height - mlx->map->camDir.z))
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
			mlx_pixel_put(mlx->mlx, mlx->win, i + k, j + mlx->map->camDir.z, color);
		}
	}
}

void	show_popup(t_mlx *mlx)
{
	if (mlx->game_server.status == CONNECTED && mlx->game_server.popup.str)
	{
		if (get_now_time() >= mlx->game_server.popup.end_at)
		{
			free(mlx->game_server.popup.str);
			mlx->game_server.popup.str = NULL;
		}
		else
		{
			mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
			mlx_string_put(mlx->mlx, mlx->win, 0, mlx->stg->height / 2, 0xFF00FF00, mlx->game_server.popup.str);
		}
	}
}

void	raycasting(t_mlx *mlx, int need_free)
{
	t_raydata	*ray[1920];
	int			i;
	int			j;
	float		factor;
	t_sprite	center_sprite;

	if (need_free)
		return ;
	i = -1;
	while (++i < mlx->stg->width)
	{
		if (i % mlx->stg->quality == 0)
		{
			ray[i] = raycast(mlx, i, false, mlx->map->playerPos);
			if (!ray[i])
				return ;
			calcul_wall_size(mlx, ray[i]);
		}
	}
	i = 0;
	while (i < mlx->stg->width)
	{
		j = MAX_HEIGHT - 1;
		while (j > 0 && !ray[i][j].found)
			j--;
		put_celling_floor(mlx, ray[i] + MAX_HEIGHT - 1, i);
		while (j >= 0)
		{
			if (ray[i][j].found)
			{
				factor = mlx->stg->height / ray[i][j].dist;
				if (ray[i][j].dir == 0)
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
		i += mlx->stg->quality;
	}
	center_sprite = draw_sprites(mlx, ray);
	put_fps(mlx, 0);
	item_effect(mlx, center_sprite);
	put_actual_weapon(mlx);
	if (mlx->stg->show_minimap)
		mini_map(mlx);
	// inventory(mlx, 0);

	char	*tmp = ft_strjoin_gnl(ft_itoa(mlx->player->ammo), " / 30");
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 150, mlx->stg->height - 210, 0xFF00FF00, tmp);
	free(tmp);
	show_popup(mlx);
}
