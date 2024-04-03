/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:38:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/03 14:08:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"
#define MOUSE_MOVE_TIME_US 1000
#define MOUSEMOVE_SENSIBILITY 0.1

void	mouse_move(t_mlx *mlx)
{
	static long long	last_update;
	int					mouseX;
	int					mouseY;
	float				move;

	if (get_now_time() - last_update < MOUSE_MOVE_TIME_US)
		return ;
	last_update = get_now_time();
	mlx_mouse_get_pos(mlx->mlx, &mouseX, &mouseY);
	move = (mouseX - MIDSCREEN_POSX) * MOUSEMOVE_SENSIBILITY;
	
	if (move != 0)
	{
		mlx->map->playerPos.h += move;
		if (mlx->map->playerPos.h < 0)
			mlx->map->playerPos.h += 360;
		if (mlx->map->playerPos.h >= 360)
			mlx->map->playerPos.h -= 360;
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
}
