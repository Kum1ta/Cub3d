/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/13 16:24:07 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	draw_square(t_mlx *mlx, int xy[2], int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (xy[0] + i < WIDTH && xy[1] + j < HEIGHT && xy[0] + i > 0 && xy[1] + j > 0)
			mlx_set_image_pixel(mlx->mlx, mlx->img, xy[0] + i, xy[1] + j, color);
			j++;
		}
		i++;
	}
}

int	set_at_finish(int key, void *finish)
{
	int	*fini;

	fini = (int *)finish;
	ft_printf("key = %d\n", key);
	if (key == 41)
		*fini = 1;
	return (0);
}

void	larg_map(t_mlx *mlx, t_block map[30][100])
{
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	while (map[i][0] != END)
	{
		j = 0;
		x = 0;
		while (map[i][j] != END)
		{
			x = j * 40;
			y = i * 40;
			if (map[i][j] == WALL)
				draw_square(mlx, (int [2]){x, y}, 40, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_printf("end\n");
}