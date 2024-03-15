/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 22:11:36 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

int	keyboard(t_mlx *mlx)
{
	if (mlx->keyboard->esc)
		close_window(0, (void *)mlx);
	if (mlx->actuel_menu == GAME || mlx->actuel_menu == MAP_LARG_MENU)
		game_keyboard(mlx);
	else if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map_keyboard(mlx);
	
	return (0);
}
