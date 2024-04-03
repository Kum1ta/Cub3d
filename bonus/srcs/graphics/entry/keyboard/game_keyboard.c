/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 15:22:11 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"
#include <time.h>

#define AMPLITUDE_VERTICAL 5
#define AMPLITUDE_HORIZONTAL 2
#define FREQUENCY 0.1
#define MOVE_TIME_US 10000

void	move_weapon(t_mlx *mlx)
{
	static long long	prev_time = 0;
	long long			current_time;
	// double				horizontal_offset;
	double				vertical_offset;

	current_time = get_now_time();
	if (mlx->player->actual_weapon == WEAPON_INV)
	{
		double elapsed_time = (double)(current_time - prev_time);
		vertical_offset = AMPLITUDE_VERTICAL * sin(FREQUENCY * elapsed_time);
		// horizontal_offset = AMPLITUDE_HORIZONTAL * sin(2 * FREQUENCY * elapsed_time);
		mlx->player->xy_item[1] = vertical_offset;
		// mlx->player->xy_item[0] = horizontal_offset;
		prev_time = current_time;
	}
}

void	move_player(t_mlx *mlx, float deltaX, float deltaY)
{
	float				angle;
	int					tmp;
	float				add_val;
	t_vec4				*ply_pos;

	move_weapon(mlx);
	tmp = mlx->map->playerPos.h - 90;
	if (tmp < 0)
		tmp += 360;
	angle = tmp * (PI / 180);
	ply_pos = &(mlx->map->playerPos);
	// move X
	{
		add_val = deltaX * cos(angle) - deltaY * sin(angle);
		t_block	block = mlx->map->blocks[(int) ply_pos->y][(int) (ply_pos->x + add_val)];
		if (block.type != WALL && (block.type != DOOR || block.data.door == true))
			ply_pos->x += add_val;
	}
	// move Y
	{
		add_val = deltaX * sin(angle) + deltaY * cos(angle);
		t_block	block = mlx->map->blocks[(int) (ply_pos->y + add_val)][(int) ply_pos->x];
		if (block.type != WALL && (block.type != DOOR || block.data.door == true))
			ply_pos->y += add_val;
	}
}

void	interract_block(t_mlx *mlx)
{
	if (mlx->player->front_ray.found && mlx->player->front_ray.dist < 2)
	{
		t_block	*front_block = mlx->player->front_ray.block;
		printf("%d == %d\n", front_block->type, DOOR);
		if (front_block->type == DOOR)
			front_block->data.door = !front_block->data.door;
	}
}

void	game_keyboard(t_mlx *mlx)
{
	static long long	lastMove;
	float add = 0.1;
	float addX;
	float addY;

	if (get_now_time() - lastMove < MOVE_TIME_US)
		return ;
	lastMove = get_now_time();
	if ((mlx->keyboard->w && mlx->keyboard->a)
		|| (mlx->keyboard->w && mlx->keyboard->d)
		|| (mlx->keyboard->s && mlx->keyboard->a)
		|| (mlx->keyboard->s && mlx->keyboard->d))
		add = add / 1.5;
	addX = (mlx->keyboard->w + -mlx->keyboard->s) * add;
	addY = (mlx->keyboard->d + -mlx->keyboard->a) * add;
	move_player(mlx, addX, addY);
	// if (mlx->keyboard->left)
	// {
	// 	mlx->map->playerPos.h -= 5.0;
	// 	if (mlx->map->playerPos.h < 0)
	// 		mlx->map->playerPos.h += 360;
	// }
	// if (mlx->keyboard->right)
	// {
	// 	mlx->map->playerPos.h += 5.0;
	// 	if (mlx->map->playerPos.h >= 360)
	// 		mlx->map->playerPos.h -= 360;
	// }
	if (mlx->keyboard->e)
		interract_block(mlx);
}
