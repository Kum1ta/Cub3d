/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:56:33 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 13:52:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	init_mouse(t_mouse *mouse)
{
	mouse->x = 0;
	mouse->y = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->pressed_left = false;
	mouse->pressed_right = false;
}

static void	init_map(t_mlx *mlx, int size)
{
	int	i;
	int	j;
	int	bigger_x;

	i = -1;
	bigger_x = 0;
	while (mlx->map->blocks[++i])
	{
		j = 0;
		while (mlx->map->blocks[i][j].type != END)
			j++;
		if (j > bigger_x)
			bigger_x = j;
	}
	mlx->menu_map->size = size;
	mlx->menu_map->width = bigger_x * mlx->menu_map->size;
	mlx->menu_map->height = i * mlx->menu_map->size;
	if ((mlx->menu_map->width > mlx->stg->width - 100 || mlx->menu_map->height > mlx->stg->height - 100) && size > 10)
		init_map(mlx, size - 1);
	else
	{
		mlx->menu_map->x = (mlx->stg->width - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (mlx->stg->height - mlx->menu_map->height) / 2;
		mlx->menu_map->initial_size = mlx->menu_map->size;
	}
}

int	init(t_mlx *mlx, t_map *map, t_settings *settings)
{
	mlx->map = map;
	mlx->stg = settings;
	mlx->menu_map = malloc(sizeof(t_menu_map));
	if (!mlx->menu_map)
		return (free_all_graphics(mlx));
	init_map(mlx, 50);
	map->playerPos.x += 0.25;
	map->playerPos.y += 0.25;
	mlx->mouse = malloc(sizeof(t_mouse));
	if (!mlx->mouse)
		return (free_all_graphics(mlx));
	init_mouse(mlx->mouse);
	mlx->actuel_menu = OPTIONS;
	mlx->selected_map = NO_MAP;
	mlx->player = malloc(sizeof(t_player));
	if (!mlx->player)
		return (free_all_graphics(mlx));
	mlx->player->health = 100;
	mlx->player->actual_weapon = WEAPON_INV;
	mlx->player->ammo = 30;
	mlx->player->is_reloading = false;
	mlx->player->xy_item[0] = 0;
	mlx->player->xy_item[1] = 0;
	mlx->map->camDir.z = 0;
	mlx->stg_win.diff = 0;
	return (0);
}
