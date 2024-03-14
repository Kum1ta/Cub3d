/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/14 17:52:41 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	exit_game(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	free_all_graphics(mlx);
	exit(0);
}

int	keyboard(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	printf("key: %d\n", key);
	mlx = (t_mlx *)mlx_ptr;
	if (key == 41)
		exit_game(mlx);
	return (0);
}
