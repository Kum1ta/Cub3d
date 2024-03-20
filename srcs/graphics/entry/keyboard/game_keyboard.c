/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 21:59:41 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	movePlayer(t_mlx *mlx, float deltaX, float deltaY)
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
	float add = 0.1;
	if ((mlx->keyboard->w && mlx->keyboard->a)
		|| (mlx->keyboard->w && mlx->keyboard->d)
		|| (mlx->keyboard->s && mlx->keyboard->a)
		|| (mlx->keyboard->s && mlx->keyboard->d))
		add = add / 1.5;
	if (mlx->keyboard->w)
		movePlayer(mlx, add, 0);
	if (mlx->keyboard->s)
		movePlayer(mlx, -add, 0);
	if (mlx->keyboard->a)
		movePlayer(mlx, 0, -add);
	if (mlx->keyboard->d)
		movePlayer(mlx, 0, add);
	if (mlx->keyboard->left)
	{
		mlx->map->playerPos.h -= 5.0;
		if (mlx->map->playerPos.h < 0)
			mlx->map->playerPos.h += 360;
	}
	if (mlx->keyboard->right)
	{
		mlx->map->playerPos.h += 5.0;
		if (mlx->map->playerPos.h >= 360)
			mlx->map->playerPos.h -= 360;
	}
}
