/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:36:01 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 15:39:21 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	main_menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
		HEIGHT / 2 - 50, 0xFFFF0000, "Main Menu");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
		HEIGHT / 2, 0xFFFF0000, "Press Enter to start");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
		HEIGHT / 2 + 50, 0xFFFF0000, "Press ESC to quit");
}