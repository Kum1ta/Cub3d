/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_larg_menu_keyboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:13:23 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 18:57:33 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	larg_map_keyboard(t_mlx *mlx)
{
	if (is_key_down(mlx->keyboard, KEY_LEFT))
		mlx->menu_map->x += 10;
	if (is_key_down(mlx->keyboard, KEY_RIGHT))
		mlx->menu_map->x -= 10;
	if (is_key_down(mlx->keyboard, KEY_UP))
		mlx->menu_map->y += 10;
	if (is_key_down(mlx->keyboard, KEY_DOWN))
		mlx->menu_map->y -= 10;
	if (is_key_down(mlx->keyboard, KEY_R))
	{
		mlx->menu_map->x = (WIDTH - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (HEIGHT - mlx->menu_map->height) / 2;
		mlx->menu_map->size = mlx->menu_map->initial_size;
	}
}
