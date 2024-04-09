/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:05:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 00:44:55 by edbernar         ###   ########.fr       */
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
	int		screenX;
}	t_sprite;

static inline float	get_distance_between_2dcoords(t_vec4 pos1, t_vec4 pos2)
{
	return (powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2));
}

static t_sprite	*get_sprite_list(t_mlx *mlx)
{
	int			i;
	t_list		*online_players;
	t_sprite	*res;

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

static void	sort_sprites(t_sprite *sprites)
{
	int			i;
	int			j;
	t_sprite	tmp;

	if (sprites->type == NONE)
		return ;
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

static void	set_sprites_screenX(t_sprite *sprites, t_vec4 plyPos, t_mlx *mlx)
{
	float	rAngle = fmod((plyPos.h + (360 - 90)), 360) * PI / 180;
	float	transform;
	float	diffX;
	float	diffY;
	float	dirX = cos(rAngle);
	float	dirY = sin(rAngle);
	float	planeX = (dirX * cos(-PI/2) - dirY * sin(-PI/2)) * (mlx->stg->fov * PI / 180);
	float	planeY = (dirX * sin(-PI/2) + dirY * cos(-PI/2)) * (mlx->stg->fov * PI / 180);
	float	invCam = 1 / (planeX * dirY - planeY * dirX);
	float	depth;

	while (sprites->type != NONE)
	{
		if (sprites->type == SPRT_PLAYER)
		{
			diffX = sprites->data.player->pos.x - plyPos.x;
			diffY = sprites->data.player->pos.y - plyPos.y;
			transform = invCam * (dirY * diffX - dirX * diffY);
			depth = invCam * (planeX * diffY - planeY * diffX);
			sprites->screenX = (mlx->stg->width / 2) * ((1 + transform / depth));
			sprites->screenX = (mlx->stg->width / 2) + ((mlx->stg->width / 2) - sprites->screenX);
		}
		sprites++;
	}
}

static void	draw_sprite(t_mlx *mlx, t_sprite *sprite, t_raydata **ray)
{
	if (sprite->screenX >= 0 && sprite->screenX <= mlx->stg->width)
	{
		for (int y = (mlx->stg->height / 2) - 5; y < (mlx->stg->height / 2) + 5; y++)
			for (int x = sprite->screenX - 5; x < sprite->screenX + 5; x++)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFFFF0000);
	}
	printf("sprite pos x: %d (screenw: %d)\n", sprite->screenX, mlx->stg->width);
}

void	draw_sprites(t_mlx *mlx, t_raydata **ray)
{
	t_sprite	*sprites;
	int			i;

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

