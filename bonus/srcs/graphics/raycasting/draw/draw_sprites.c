/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:05:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/18 13:28:38 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static t_sprite *get_sprite_list(t_mlx *mlx)
{
	int i;
	t_list *online_players;
	t_list *kits;
	t_sprite *res;

	i = 0;
	if (mlx->game_server.status == CONNECTED)
	{
		online_players = mlx->game_server.online_player;
		while (online_players)
		{
			i++;
			online_players = online_players->next;
		}
		kits = mlx->game_server.kits;
		while (kits)
		{
			i++;
			kits = kits->next;
		}
	}

	res = malloc((i + 1) * sizeof(t_sprite));
	if (!res)
		return (NULL);
	i = 0;
	if (mlx->game_server.status == CONNECTED)
	{
		online_players = mlx->game_server.online_player;
		while (online_players)
		{
			res[i].e_type = SPRT_PLAYER;
			res[i].u_data.player = online_players->content;
			res[i].dist = get_distance_between_2dcoords(mlx->map->player_pos, res[i].u_data.player->pos);
			i++;
			online_players = online_players->next;
		}
		kits = mlx->game_server.kits;
		while (kits)
		{
			res[i].e_type = SPRT_HEALTH_KIT;
			res[i].u_data.kit = kits->content;
			res[i].dist = get_distance_between_2dcoords(mlx->map->player_pos, res[i].u_data.kit->pos);
			i++;
			kits = kits->next;
		}
	}
	res[i].e_type = NONE;
	return (res);
}

static void sort_sprites(t_sprite *sprites)
{
	int i;
	int j;
	t_sprite tmp;

	if (sprites->e_type == NONE)
		return;
	i = 0;
	while (sprites[i + 1].e_type != NONE)
	{
		j = i + 1;
		while (sprites[j].e_type != NONE)
		{
			if (sprites[j].dist > sprites[i].dist)
			{
				tmp = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void set_sprites_screen_x(t_sprite *sprites, t_vec3 plyPos, t_mlx *mlx)
{
	float transform;
	float diffX;
	float diffY;
	float dirX = mlx->map->cam_dir.x;
	float dirY = mlx->map->cam_dir.y;
	float planeX = mlx->map->cam_plane.x;
	float planeY = mlx->map->cam_plane.y;
	float invCam = 1 / (planeX * dirY - planeY * dirX);

	while (sprites->e_type != NONE)
	{
		if (sprites->e_type == SPRT_PLAYER)
		{
			diffX = sprites->u_data.player->pos.x - plyPos.x;
			diffY = sprites->u_data.player->pos.y - plyPos.y;
		}
		else
		{
			diffX = sprites->u_data.kit->pos.x - plyPos.x;
			diffY = sprites->u_data.kit->pos.y - plyPos.y;
		}
		transform = invCam * (dirY * diffX - dirX * diffY);
		sprites->depth = invCam * (planeX * diffY - planeY * diffX);
		sprites->screen_x = (mlx->stg->width / 2) * ((1 + transform / sprites->depth));
		sprites++;
	}
}

static t_img *get_sprite_img(t_mlx *mlx, t_sprite *sprite)
{
	float	dx;
	float	dy;
	int		rot;

	if (sprite->e_type == SPRT_PLAYER)
	{
		dx = mlx->map->player_pos.x - sprite->u_data.player->pos.x;
		dy = mlx->map->player_pos.y - sprite->u_data.player->pos.y;
		rot = (atan2(dy, dx) + atan2(sprite->u_data.player->dir.y, sprite->u_data.player->dir.x)) * 180 / PI;
		while (rot < 0)
			rot += 360;
		return (mlx->textures->player + ((int)(rot / 90 % 4)));
	}
	else if (sprite->e_type == SPRT_HEALTH_KIT)
		return (&mlx->textures->health_kit);
	return (NULL);
}

static bool	draw_sprite(t_mlx *mlx, t_sprite *sprite, t_raydata **ray)
{
	int		width;
	int		height;
	int		startX;
	int		startY;
	int		x;
	int		y;
	int		imgX;
	int		imgY;
	int		color;
	bool	touch_center;
	t_img	*img;

	img = get_sprite_img(mlx, sprite);
	touch_center = false;
	width = mlx->stg->height / sprite->depth;
	height = mlx->stg->height / sprite->depth;
	if (img && sprite->depth > 0 && sprite->screen_x + width / 2 >= 0 && sprite->screen_x - width / 2 < mlx->stg->width)
	{
		startX = sprite->screen_x - width / 2;
		x = startX;
		while (x - startX < width)
		{
			if (x >= 0 && x < mlx->stg->width && sprite->depth < ray[x]->dist)
			{
				imgX = ((float) (x - startX)) / ((float) width) * img->width;
				startY = mlx->stg->height / 2 - height / 2;
				y = startY;
				while (y - startY < height)
				{
					imgY = ((float) (y - startY)) / ((float) height) * img->height;
					if (y + mlx->map->cam_dir.z >= 0 && y + mlx->map->cam_dir.z < mlx->stg->height)
					{
						color = mlx_get_image_pixel(mlx->mlx, img->img, imgX, imgY);
						if (color >> 24 & 0xFF == 0xFF)
						{
							mlx_pixel_put(mlx->mlx, mlx->win, x, y + mlx->map->cam_dir.z, color);
							if (x == mlx->stg->width / 2 && y + mlx->map->cam_dir.z == mlx->stg->height / 2)
								touch_center = true;
						}
					}
					y++;
				}
			}
			x++;
		}
	}
	return (touch_center);
}

t_sprite	draw_sprites(t_mlx *mlx, t_raydata **ray)
{
	t_sprite	*sprites;
	t_sprite	center_sprite;
	int i;

	sprites = get_sprite_list(mlx);
	center_sprite.e_type = NONE;
	if (!sprites)
		return (center_sprite);
	sort_sprites(sprites);
	set_sprites_screen_x(sprites, mlx->map->player_pos, mlx);
	i = 0;
	while (sprites[i].e_type != NONE)
	{
		if (sprites[i].e_type != SPRT_PLAYER || sprites[i].u_data.player->health > 0)
			if (draw_sprite(mlx, sprites + i, ray))
				center_sprite = sprites[i];
		i++;
	}
	free(sprites);
	return (center_sprite);
}
