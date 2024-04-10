/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:05:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 22:48:39 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

typedef struct s_sprite
{
	enum
	{
		NONE,
		SPRT_PLAYER
	} type;
	union
	{
		t_online_player *player;
	} data;
	float	dist;
	float	depth;
	int 	screenX;
} t_sprite;

static inline float get_distance_between_2dcoords(t_vec3 pos1, t_vec3 pos2)
{
	return (powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2));
}

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

static void draw_sprite(t_mlx *mlx, t_sprite *sprite, t_raydata **ray)
{
	int	width;
	int	height;
	int	startX;
	int	startY;
	int	x;
	int	y;
	int	imgX;
	int	imgY;
	int	color;

	width = mlx->stg->height / sprite->depth;
	height = mlx->stg->height / sprite->depth;
	if (sprite->depth > 0 && sprite->screenX + width / 2 >= 0 && sprite->screenX - width / 2 < mlx->stg->width)
	{
		startX = sprite->screenX - width / 2;
		x = startX;
		while (x - startX < width)
		{
			if (x >= 0 && x < mlx->stg->width && sprite->depth < ray[x]->dist)
			{
				imgX = ((float) (x - startX)) / ((float) width) * mlx->textures->player.width;
				startY = mlx->stg->height / 2 - height / 2;
				y = startY;
				while (y - startY < height)
				{
					imgY = ((float) (y - startY)) / ((float) height) * mlx->textures->player.height;
					if (y + mlx->map->camDir.z >= 0 && y + mlx->map->camDir.z < mlx->stg->height)
					{
						color = mlx_get_image_pixel(mlx->mlx, mlx->textures->player.img, imgX, imgY);
						if (color >> 24 & 0xFF)
							mlx_pixel_put(mlx->mlx, mlx->win, x, y + mlx->map->camDir.z, color);
					}
					y++;
				}
			}
			x++;
		}
	}
}

void draw_sprites(t_mlx *mlx, t_raydata **ray)
{
	t_sprite *sprites;
	int i;

	sprites = get_sprite_list(mlx);
	sort_sprites(sprites);
	set_sprites_screenX(sprites, mlx->map->playerPos, mlx);
	i = 0;
	while (sprites[i].type != NONE)
	{
		draw_sprite(mlx, sprites + i, ray);
		i++;
	}
	free(sprites);
}
