/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 21:14:40 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	move_player(t_mlx *mlx, float deltaX, float deltaY)
{
	float	angle;
	int		tmp;

	tmp = mlx->map->playerPos.h - 90;
	if (tmp < 0)
		tmp += 360;
	angle = tmp * (PI / 180);
	mlx->map->playerPos.x += deltaX * cos(angle) - deltaY * sin(angle);
	mlx->map->playerPos.y += deltaX * sin(angle) + deltaY * cos(angle);
}

void	game_keyboard(t_mlx *mlx)
{
	float	add;

	add = 0.1;
	if ((mlx->keyboard->w && mlx->keyboard->a) || (mlx->keyboard->w
			&& mlx->keyboard->d) || (mlx->keyboard->s && mlx->keyboard->a)
		|| (mlx->keyboard->s && mlx->keyboard->d))
		add = add / 1.5;
	if (mlx->keyboard->w)
		move_player(mlx, add, 0);
	if (mlx->keyboard->s)
		move_player(mlx, -add, 0);
	if (mlx->keyboard->a)
		move_player(mlx, 0, -add);
	if (mlx->keyboard->d)
		move_player(mlx, 0, add);
	if (mlx->keyboard->left)
		mlx->map->playerPos.h -= 5.0;
	if (mlx->keyboard->right)
		mlx->map->playerPos.h += 5.0;
	if (mlx->map->playerPos.h >= 360)
		mlx->map->playerPos.h -= 360;
	if (mlx->map->playerPos.h < 0)
		mlx->map->playerPos.h += 360;
}
