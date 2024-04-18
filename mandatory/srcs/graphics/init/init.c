/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:56:33 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 21:39:46 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	init_keyboard(t_keyboard *keyboard)
{
	keyboard->w = false;
	keyboard->a = false;
	keyboard->s = false;
	keyboard->d = false;
	keyboard->r = false;
	keyboard->up = false;
	keyboard->down = false;
	keyboard->left = false;
	keyboard->right = false;
	keyboard->esc = false;
}

static void	init_map(t_mlx *mlx, int size)
{
	int	i[2];
	int	bigger_x;

	i[0] = -1;
	bigger_x = 0;
	while (mlx->map->blocks[++i[0]])
	{
		i[1] = 0;
		while (mlx->map->blocks[i[0]][i[1]] != END)
			i[1]++;
		if (i[1] > bigger_x)
			bigger_x = i[1];
	}
	mlx->menu_map->size = size;
	mlx->menu_map->width = bigger_x * mlx->menu_map->size;
	mlx->menu_map->height = i[0] * mlx->menu_map->size;
	if ((mlx->menu_map->width > WIDTH - 100
			|| mlx->menu_map->height > HEIGHT - 100) && size > 10)
		init_map(mlx, size - 1);
	else
	{
		mlx->menu_map->x = (WIDTH - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (HEIGHT - mlx->menu_map->height) / 2;
		mlx->menu_map->initial_size = mlx->menu_map->size;
	}
}

int	init(t_mlx *mlx, t_map *map)
{
	mlx->map = map;
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->keyboard = NULL;
	mlx->menu_map = malloc(sizeof(t_menu_map));
	if (!mlx->menu_map)
		return (free_all_graphics(mlx));
	init_map(mlx, 50);
	map->player_pos.x += 0.25;
	map->player_pos.y += 0.25;
	mlx->actuel_menu = GAME;
	mlx->keyboard = malloc(sizeof(t_keyboard));
	if (!mlx->keyboard)
		return (free_all_graphics(mlx));
	init_keyboard(mlx->keyboard);
	return (0);
}
