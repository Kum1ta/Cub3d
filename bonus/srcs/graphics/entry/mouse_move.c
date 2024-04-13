/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:38:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/13 16:51:13 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"
#define MOUSE_MOVE_TIME_US 1000
#define MOUSEMOVE_SENSIBILITY_X 0.004
#define MOUSEMOVE_SENSIBILITY_Y 1

void	mouse_move(t_mlx *mlx)
{
	static long long	last_update;
	int					mouseX;
	int					mouseY;
	float				move_x;
	float				move_y;
	float				tmp;

	if (get_now_time() - last_update < MOUSE_MOVE_TIME_US)
		return ;
	last_update = get_now_time();
	mlx_mouse_get_pos(mlx->mlx, &mouseX, &mouseY);
	move_x = (mouseX - MIDSCREEN_POSX) * MOUSEMOVE_SENSIBILITY_X;
	if (move_x != 0)
	{
		tmp = mlx->map->camDir.x;
		mlx->map->camDir.x = (mlx->map->camDir.x * cos(move_x)) - (mlx->map->camDir.y * sin(move_x));
		mlx->map->camDir.y = (tmp * sin(move_x)) + (mlx->map->camDir.y * cos(move_x));
		tmp = mlx->map->camPlane.x;
		mlx->map->camPlane.x = (mlx->map->camPlane.x * cos(move_x)) - (mlx->map->camPlane.y * sin(move_x));
		mlx->map->camPlane.y = (tmp * sin(move_x)) + (mlx->map->camPlane.y * cos(move_x));
		if (mlx->game_server.status == CONNECTED)
			dprintf(mlx->game_server.sockfd, "setDir:%.2f,%.2f;", mlx->map->camDir.x, mlx->map->camDir.y);
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
	move_y = (mouseY - MIDSCREEN_POSY) * MOUSEMOVE_SENSIBILITY_Y;
	if (move_y != 0)
	{
		mlx->map->camDir.z -= move_y;
		if (mlx->map->camDir.z < -1000)
			mlx->map->camDir.z = -1000;
		if (mlx->map->camDir.z > 1000)
			mlx->map->camDir.z = 1000;
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
}
