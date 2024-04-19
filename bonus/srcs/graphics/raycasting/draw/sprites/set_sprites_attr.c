/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites_attr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:16:42 by psalame           #+#    #+#             */
/*   Updated: 2024/04/19 13:02:07 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites_Int.h"

void	set_sprites_screen_x(t_sprite *sprites, t_vec3 plyPos, t_mlx *mlx)
{
	float			transform;
	t_vec2			diff;
	const t_vec3	*dir = &mlx->map->cam_dir;
	const t_vec2	*plane = &mlx->map->cam_plane;
	const float		inv_cam = 1 / (plane->x * dir->y - plane->y * dir->x);

	while (sprites->e_type != NONE)
	{
		if (sprites->e_type == SPRT_PLAYER)
			diff.x = sprites->u_data.player->pos.x - plyPos.x;
		else
			diff.x = sprites->u_data.kit->pos.x - plyPos.x;
		if (sprites->e_type == SPRT_PLAYER)
			diff.y = sprites->u_data.player->pos.y - plyPos.y;
		else
			diff.y = sprites->u_data.kit->pos.y - plyPos.y;
		transform = inv_cam * (dir->y * diff.x - dir->x * diff.y);
		sprites->depth = inv_cam * (plane->x * diff.y - plane->y * diff.x);
		if (sprites->depth == 0.0f)
			sprites->depth = (float)INT_MAX;
		sprites->screen_x = (mlx->stg->width / 2)
			* ((1 + transform / sprites->depth));
		sprites++;
	}
}

void	set_sprite_img(t_mlx *mlx, t_sprite *sprite)
{
	float	dx;
	float	dy;
	int		rot;
	t_vec2	*sprt_dir;

	if (sprite->e_type == SPRT_PLAYER)
	{
		dx = mlx->map->player_pos.x - sprite->u_data.player->pos.x;
		dy = mlx->map->player_pos.y - sprite->u_data.player->pos.y;
		sprt_dir = &sprite->u_data.player->dir;
		rot = (atan2(dy, dx) + atan2(sprt_dir->y, sprt_dir->x)) * 180 / PI;
		while (rot < 0)
			rot += 360;
		sprite->txt = mlx->textures->player + ((int)(rot / 90 % 4));
	}
	else if (sprite->e_type == SPRT_HEALTH_KIT)
		sprite->txt = &mlx->textures->health_kit;
}
