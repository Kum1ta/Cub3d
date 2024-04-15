/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:05:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/15 14:33:03 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static t_sprite *get_sprite_list(t_mlx *mlx)
{
	int i;
	t_list *online_players;
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
			res[i].type = SPRT_PLAYER;
			res[i].data.player = online_players->content;
			res[i].dist = get_distance_between_2dcoords(mlx->map->playerPos, res[i].data.player->pos);
			i++;
			online_players = online_players->next;
		}
	}
	res[i].type = NONE;
	return (res);
}

static void sort_sprites(t_sprite *sprites)
{
	int i;
	int j;
	t_sprite tmp;

	if (sprites->type == NONE)
		return;
	i = 0;
	while (sprites[i + 1].type != NONE)
	{
		j = i + 1;
		while (sprites[j].type != NONE)
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

static void set_sprites_screenX(t_sprite *sprites, t_vec3 plyPos, t_mlx *mlx)
{
	float transform;
	float diffX;
	float diffY;
	float dirX = mlx->map->camDir.x;
	float dirY = mlx->map->camDir.y;
	float planeX = mlx->map->camPlane.x;
	float planeY = mlx->map->camPlane.y;
	float invCam = 1 / (planeX * dirY - planeY * dirX);

	while (sprites->type != NONE)
	{
		if (sprites->type == SPRT_PLAYER)
		{
			diffX = sprites->data.player->pos.x - plyPos.x;
			diffY = sprites->data.player->pos.y - plyPos.y;
			transform = invCam * (dirY * diffX - dirX * diffY);
			sprites->depth = invCam * (planeX * diffY - planeY * diffX);
			sprites->screenX = (mlx->stg->width / 2) * ((1 + transform / sprites->depth));
		}
		sprites++;
	}
}

static t_img *get_sprite_img(t_mlx *mlx, t_sprite *sprite)
{
	float	dx;
	float	dy;
	int		rot;

	if (sprite->type == SPRT_PLAYER)
	{
		dx = mlx->map->playerPos.x - sprite->data.player->pos.x;
		dy = mlx->map->playerPos.y - sprite->data.player->pos.y;
		rot = (atan2(dy, dx) + atan2(sprite->data.player->dir.y, sprite->data.player->dir.x)) * 180 / PI;
		while (rot < 0)
			rot += 360;
		return (mlx->textures->player + ((int)(rot / 90 % 4)));
	}
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
	if (img && sprite->depth > 0 && sprite->screenX + width / 2 >= 0 && sprite->screenX - width / 2 < mlx->stg->width)
	{
		startX = sprite->screenX - width / 2;
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
					if (y + mlx->map->camDir.z >= 0 && y + mlx->map->camDir.z < mlx->stg->height)
					{
						color = mlx_get_image_pixel(mlx->mlx, img->img, imgX, imgY);
						if (color >> 24 & 0xFF == 0xFF)
						{
							mlx_pixel_put(mlx->mlx, mlx->win, x, y + mlx->map->camDir.z, color);
							if (x == mlx->stg->width / 2 && y + mlx->map->camDir.z == mlx->stg->height / 2)
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
	if (!sprites)
		return ;
	sort_sprites(sprites);
	set_sprites_screenX(sprites, mlx->map->playerPos, mlx);
	i = 0;
	center_sprite.type = NONE;
	while (sprites[i].type != NONE)
	{
		if (sprites[i].type != SPRT_PLAYER || sprites[i].data.player->health > 0)
			if (draw_sprite(mlx, sprites + i, ray))
				center_sprite = sprites[i];
		i++;
	}
	free(sprites);
	return (center_sprite);
}
