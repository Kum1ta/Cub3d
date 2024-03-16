/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 17:06:48 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	game_keyboard(t_mlx *mlx)
{
	float	add;

	add = 0.1;
	/******** POUR LE DEBUT, CA SERA CHANGÉ PLUS TARD MAIS PEUT ETRE GARDÉ POUR AUTRE CHOSE ********/
	if ((mlx->keyboard->w && mlx->keyboard->a)
		|| (mlx->keyboard->w && mlx->keyboard->d)
		|| (mlx->keyboard->s && mlx->keyboard->a)
		|| (mlx->keyboard->s && mlx->keyboard->d))
		add = add / 1.5;
	if (mlx->keyboard->w)
		mlx->map->playerPos.y -= add;
	if (mlx->keyboard->s)
		mlx->map->playerPos.y += add;
	if (mlx->keyboard->a)
		mlx->map->playerPos.x -= add;
	if (mlx->keyboard->d)
		mlx->map->playerPos.x += add;
	/*********************************************************************************************/
}