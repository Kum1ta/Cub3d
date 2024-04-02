/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_larg_menu_keyboard.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:13:23 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 17:02:38 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	larg_map_keyboard(t_mlx *mlx)
{
	if (mlx->keyboard->left)
		mlx->menu_map->x += 10;
	if (mlx->keyboard->right)
		mlx->menu_map->x -= 10;
	if (mlx->keyboard->up)
		mlx->menu_map->y += 10;
	if (mlx->keyboard->down)
		mlx->menu_map->y -= 10;
	if (mlx->keyboard->r)
	{
		mlx->menu_map->x = (WIDTH - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (HEIGHT - mlx->menu_map->height) / 2;
		mlx->menu_map->size = mlx->menu_map->initial_size;
	}
}
