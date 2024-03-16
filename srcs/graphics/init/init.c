/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:56:33 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 17:02:27 by edbernar         ###   ########.fr       */
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
	int	i;
	int	j;
	int	bigger_x;

	i = 0;
	bigger_x = 0;
	while (mlx->map->blocks[i])
	{
		j = 0;
		while (mlx->map->blocks[i][j] != END)
			j++;
		if (j > bigger_x)
			bigger_x = j;
		i++;
	}
	mlx->menu_map->size = size;
	mlx->menu_map->width = bigger_x * mlx->menu_map->size;
	mlx->menu_map->height = i * mlx->menu_map->size;
	if ((mlx->menu_map->width > WIDTH || mlx->menu_map->height > HEIGHT) && size > 10)
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
	mlx->mouse = NULL;
	mlx->keyboard = NULL;
	mlx->menu_map = malloc(sizeof(t_menu_map));
	if (!mlx->menu_map)
		return (free_all_graphics(mlx));
	init_map(mlx, 50);
	mlx->mouse = malloc(sizeof(t_mouse));
	if (!mlx->mouse)
		return (free_all_graphics(mlx));
	init_mouse(mlx->mouse);
	mlx->actuel_menu = GAME;
	mlx->keyboard = malloc(sizeof(t_keyboard));
	if (!mlx->keyboard)
		return (free_all_graphics(mlx));
	init_keyboard(mlx->keyboard);
	return (0);
}