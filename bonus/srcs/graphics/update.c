/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:53:45 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 15:18:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	mouse_move(mlx);
	mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->player->health <= 0)
	{
		mlx_mouse_show();
		mlx->actuel_menu = NOTHING;
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "You died");
	}
	else if (mlx->actuel_menu == MAP_LARG_MENU)
	{
		mlx_mouse_show();
		larg_map(mlx, 0);
	}
	else if (mlx->actuel_menu == GAME)
	{
		mlx_mouse_hide();
		raycasting(mlx, 0);
	}
	else
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "Error");
	return (0);
}
