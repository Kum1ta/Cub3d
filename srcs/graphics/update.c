/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:53:45 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 21:02:00 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;
	long long			now;

	now = get_now_time();
	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->player->health <= 0)
	{
		mlx->actuel_menu = NOTHING;
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "You died");
	}
	else if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map(mlx, 0);
	else if (mlx->actuel_menu == GAME)
		raycasting(mlx, 0);
	else
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "Error");
	put_fps(mlx, 0);
	info_player(mlx);
	if (now - get_now_time() < TIME_PER_FRAME_US * 1000)
		wait_us(TIME_PER_FRAME_US - (now - get_now_time()));
	return (0);
}
