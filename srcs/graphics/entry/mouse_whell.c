/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_whell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:39:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 17:05:12 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	larg_map_menu_wheel(int button, t_mlx *mlx)
{
	if (button == 1 && mlx->menu_map->size < 100)
		mlx->menu_map->size *= 1.2;
	else if (button == 2 && mlx->menu_map->size > 10)
		mlx->menu_map->size /= 1.2;
}

int	mouse_whell(int button, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map_menu_wheel(button, mlx);
	return (0);
}
