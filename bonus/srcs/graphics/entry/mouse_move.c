/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:38:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/06 20:09:24 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"
#define MOUSE_MOVE_TIME_US 1000
#define MOUSEMOVE_SENSIBILITY_X 0.1
#define MOUSEMOVE_SENSIBILITY_Y 0.5

void	mouse_move(t_mlx *mlx)
{
	static long long	last_update;
	int					mouseX;
	int					mouseY;
	float				move_x;
	float				move_y;

	if (get_now_time() - last_update < MOUSE_MOVE_TIME_US)
		return ;
	last_update = get_now_time();
	mlx_mouse_get_pos(mlx->mlx, &mouseX, &mouseY);
	move_x = (mouseX - MIDSCREEN_POSX) * MOUSEMOVE_SENSIBILITY_X;
	if (move_x != 0)
	{
		mlx->map->playerPos.h += move_x;
		if (mlx->map->playerPos.h < 0)
			mlx->map->playerPos.h += 360;
		if (mlx->map->playerPos.h >= 360)
			mlx->map->playerPos.h -= 360;
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
	move_y = (mouseY - MIDSCREEN_POSY) * MOUSEMOVE_SENSIBILITY_Y;
	if (move_y != 0)
	{
		mlx->map->playerPos.v -= move_y;
		if (mlx->map->playerPos.v < -1000)
			mlx->map->playerPos.v = -1000;
		if (mlx->map->playerPos.v > 1000)
			mlx->map->playerPos.v = 1000;
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
}
