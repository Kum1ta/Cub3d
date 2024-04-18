/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:05:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/18 14:42:21 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites_Int.h"

static void	sort_sprites(t_sprite *sprites)
{
	int			i;
	int			j;
	t_sprite	tmp;

	if (sprites->e_type == NONE)
		return ;
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

t_sprite	draw_sprites(t_mlx *mlx, t_raydata **ray)
{
	t_sprite	*sprites;
	t_sprite	center_sprite;
	int			i;

	sprites = get_sprite_list(mlx);
	center_sprite.e_type = NONE;
	if (!sprites)
		return (center_sprite);
	sort_sprites(sprites);
	set_sprites_screen_x(sprites, mlx->map->player_pos, mlx);
	i = 0;
	while (sprites[i].e_type != NONE)
	{
		if (sprites[i].e_type != SPRT_PLAYER
			|| sprites[i].u_data.player->health > 0)
		{
			set_sprite_img(mlx, sprites + i);
			if (draw_sprite(mlx, sprites + i, ray))
				center_sprite = sprites[i];
		}
		i++;
	}
	free(sprites);
	return (center_sprite);
}
