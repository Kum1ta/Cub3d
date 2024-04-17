/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 17:18:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"
#include <time.h>

#define MOVE_TIME_US 1/40*1000000

void	move_player(t_mlx *mlx, float deltaX, float deltaY)
{
	float				add_val;
	t_vec3				*ply_pos;
	t_block				block;

	ply_pos = &(mlx->map->playerPos);
	add_val = deltaX * mlx->map->camDir.x - deltaY * mlx->map->camDir.y;
	block = mlx->map->blocks[(int) ply_pos->y][(int) (ply_pos->x + add_val)];
	if (block.type != WALL && (block.type != DOOR || block.data.door == true))
		ply_pos->x += add_val;
	add_val = deltaX * mlx->map->camDir.y + deltaY * mlx->map->camDir.x;
	block = mlx->map->blocks[(int) (ply_pos->y + add_val)][(int) ply_pos->x];
	if (block.type != WALL && (block.type != DOOR || block.data.door == true))
		ply_pos->y += add_val;
	if (mlx->game_server.status == CONNECTED)
		dprintf(mlx->game_server.sockfd, "setPos:%.2f,%.2f,%.2f;",
			ply_pos->x, ply_pos->y, ply_pos->z);
}

void	interract_block(t_mlx *mlx)
{
	t_raydata	*front_ray;

	front_ray = raycast(mlx, mlx->stg->width / 2, true, mlx->map->playerPos);
	if (front_ray->found && front_ray->dist < 2)
	{
		t_block	*front_block = front_ray->block;
		if (front_block->type == DOOR)
		{
			front_block->data.door = !front_block->data.door;
			if (mlx->game_server.status == CONNECTED)
				ft_dprintf(mlx->game_server.sockfd, "setDoorState:%d,%d,%d;", front_block->data.door, (int) front_ray->pos.x, (int) front_ray->pos.y);
		}
	}
}

void	game_keyboard(t_mlx *mlx)
{
	static long long	lastMove;
	float add = 0.15;
	float addX;
	float addY;

	if (get_now_time() - lastMove < MOVE_TIME_US)
		return ;
	lastMove = get_now_time();
	if ((is_key_down(mlx->keyboard, KEY_W) && is_key_down(mlx->keyboard, KEY_A))
		|| (is_key_down(mlx->keyboard, KEY_W) && is_key_down(mlx->keyboard, KEY_D))
		|| (is_key_down(mlx->keyboard, KEY_S) && is_key_down(mlx->keyboard, KEY_A))
		|| (is_key_down(mlx->keyboard, KEY_S) && is_key_down(mlx->keyboard, KEY_D)))
		add = add / 1.5;
	addX = (is_key_down(mlx->keyboard, KEY_W) + -is_key_down(mlx->keyboard, KEY_S)) * add;
	addY = (is_key_down(mlx->keyboard, KEY_D) + -is_key_down(mlx->keyboard, KEY_A)) * add;
	if (addX || addY)
		move_player(mlx, addX, addY);
	if (is_key_down(mlx->keyboard, KEY_UP))
		mlx->just_try += 25;
	if (is_key_down(mlx->keyboard, KEY_DOWN))
		mlx->just_try -= 25;
	if (is_key_just_down(mlx->keyboard, KEY_E))
		interract_block(mlx);
}
