/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:38:46 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 17:27:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"
#define MOUSE_MOVE_TIME_US 1/40*1000000
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
		tmp = mlx->map->cam_dir.x;
		mlx->map->cam_dir.x = (mlx->map->cam_dir.x * cos(move_x)) - (mlx->map->cam_dir.y * sin(move_x));
		mlx->map->cam_dir.y = (tmp * sin(move_x)) + (mlx->map->cam_dir.y * cos(move_x));
		tmp = mlx->map->cam_plane.x;
		mlx->map->cam_plane.x = (mlx->map->cam_plane.x * cos(move_x)) - (mlx->map->cam_plane.y * sin(move_x));
		mlx->map->cam_plane.y = (tmp * sin(move_x)) + (mlx->map->cam_plane.y * cos(move_x));
		if (mlx->game_server.status == CONNECTED)
			dprintf(mlx->game_server.sockfd, "setDir:%.2f,%.2f;", mlx->map->cam_dir.x, mlx->map->cam_dir.y);
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
	move_y = (mouseY - MIDSCREEN_POSY) * MOUSEMOVE_SENSIBILITY_Y;
	if (move_y != 0)
	{
		mlx->map->cam_dir.z -= move_y;
		if (mlx->map->cam_dir.z < -1000)
			mlx->map->cam_dir.z = -1000;
		if (mlx->map->cam_dir.z > 1000)
			mlx->map->cam_dir.z = 1000;
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
	}
}
