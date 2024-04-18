/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:51:53 by psalame           #+#    #+#             */
/*   Updated: 2024/04/18 13:26:24 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static inline void	replace_weapon(t_mlx *mlx, long long *last_time)
{
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

static inline void	weapon_shoot(t_mlx *mlx, long long *last_time,
								t_sprite center_sprite)
{
	int			player_touch;
	const int	fire_pos[2] = {mlx->stg->width * 0.58 - 150 / 2,
		mlx->stg->height * 0.55 - 150 / 2};

	player_touch = -1;
	fire_pos[0];
	system("paplay --volume=65535 ./sounds/game/weapon_fire.wav &");
	*last_time = get_now_time();
	mlx->player->ammo--;
	draw_image_to_window(mlx, &mlx->textures->fire_gun,
		fire_pos, (int [2]){150, 150});
	if (mlx->game_server.status == CONNECTED)
	{
		player_touch = -1;
		if (center_sprite.e_type == SPRT_PLAYER)
			player_touch = center_sprite.u_data.player->server_id;
		if (player_touch != -1)
			system("paplay --volume=30000 ./sounds/game/hit.wav &");
		dprintf(mlx->game_server.sockfd, "shoot:%d,%.2f,%.2f,%.2f;",
			player_touch, mlx->map->player_pos.x, mlx->map->player_pos.y,
			mlx->map->player_pos.z);
	}
	mlx->player->xy_item[0] = 10;
	mlx->player->xy_item[1] = 10;
}

void	weapon_effect(t_mlx *mlx, long long *last_time, t_sprite center_sprite)
{
	if (!mlx->player->is_reloading
		&& (mlx->mouse->pressed_left
			&& (get_now_time() - *last_time > 150000))
		&& mlx->player->ammo)
		weapon_shoot(mlx, last_time, center_sprite);
	if (!mlx->player->is_reloading && is_key_down(mlx->keyboard, KEY_R)
		&& get_now_time() - *last_time > 50000 && mlx->player->ammo < 30)
	{
		system("paplay --volume=50000 ./sounds/game/weapon_reload.wav &");
		*last_time = get_now_time();
		mlx->player->is_reloading = true;
	}
	replace_weapon(mlx, last_time);
}

void	knife_effect(t_mlx *mlx, long long *last_time, t_sprite center_sprite)
{
	int	player_touch;

	if (mlx->mouse->pressed_left && get_now_time() - *last_time > 500000)
	{
		system("paplay --volume=65535 ./sounds/game/cut_hit.wav &");
		*last_time = get_now_time();
		if (mlx->game_server.status == CONNECTED)
		{
			player_touch = -1;
			if (center_sprite.e_type == SPRT_PLAYER && center_sprite.dist < 2)
				player_touch = center_sprite.u_data.player->server_id;
			if (player_touch != -1)
				system("paplay --volume=30000 ./sounds/game/hit.wav &");
			dprintf(mlx->game_server.sockfd, "cut:%d,%.2f,%.2f,%.2f;",
				player_touch, mlx->map->player_pos.x, mlx->map->player_pos.y,
				mlx->map->player_pos.z);
		}
		mlx->player->xy_item[0] = 150;
		mlx->player->xy_item[1] = 150;
		return ;
	}
	if (mlx->player->xy_item[0] > 0)
		mlx->player->xy_item[0] -= 10;
	if (mlx->player->xy_item[1] > 0)
		mlx->player->xy_item[1] -= 10;
}

void	item_effect(t_mlx *mlx, t_sprite center_sprite)
{
	static long long	last_time = 0;

	if (mlx->player->actual_weapon == WEAPON_INV)
		weapon_effect(mlx, &last_time, center_sprite);
	else if (mlx->player->actual_weapon == KNIFE_INV)
		knife_effect(mlx, &last_time, center_sprite);
}
