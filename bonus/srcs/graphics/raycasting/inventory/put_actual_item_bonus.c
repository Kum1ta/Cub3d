/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_actual_item.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:10:00 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 18:33:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static void	put_ammo(t_mlx *mlx)
{
	static char	str[] = "00 / 30";

	str[0] = mlx->player->ammo / 10 + '0';
	str[1] = mlx->player->ammo % 10 + '0';
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 20.0f);
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 150,
		mlx->stg->height - 210, 0xFF00FF00, str);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
}

static inline void	draw_cursor(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 20)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 10 + i,
			mlx->stg->height / 2, 0xFF00FF00);
	i = -1;
	while (++i < 20)
		mlx_pixel_put(mlx->mlx, mlx->win, mlx->stg->width / 2,
			mlx->stg->height / 2 - 10 + i, 0xFF00FF00);
}

static inline void	draw_weapon(t_mlx *mlx)
{
	int	wpn_pos[2];
	int	wpn_size[2];

	wpn_size[0] = mlx->textures->weapon_game.width * mlx->stg->width / 1920;
	wpn_size[1] = mlx->textures->weapon_game.height * mlx->stg->height / 1080;
	wpn_pos[0] = mlx->stg->width - wpn_size[0] + mlx->player->xy_item[0];
	wpn_pos[1] = mlx->stg->height - wpn_size[1] + mlx->player->xy_item[1];
	draw_image_to_window(mlx, &mlx->textures->weapon_game, wpn_pos, wpn_size);
	put_ammo(mlx);
}

static inline void	draw_knife(t_mlx *mlx)
{
	draw_image_to_window(mlx, &mlx->textures->knife_game,
		(int [2]){mlx->stg->width - 300 - mlx->player->xy_item[0],
		mlx->stg->height - 250 - mlx->player->xy_item[1]},
		(int [2]){400, 400});
}

void	put_actual_item(t_mlx *mlx)
{
	draw_cursor(mlx);
	if (mlx->player->actual_weapon == WEAPON_INV)
		draw_weapon(mlx);
	else if (mlx->player->actual_weapon == KNIFE_INV)
		draw_knife(mlx);
}
