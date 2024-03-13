/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/13 22:02:50 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
}

int	update(void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	larg_map(mlx);
	if (mlx->img)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	close_window(int event, void *mlx_ptr)
{
	t_mlx	*mlx;

	if	(event == 0 || event == 41)
	{
		mlx = (t_mlx *)mlx_ptr;
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free_all_graphics(mlx);
		exit(0);
	}
	return (0);
}

// void	graphics_part(t_map *map)
void	graphics_part(t_block map[30][100])
{
	(void)map;
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	init_mlx(mlx);
	/*****JUSTE TANT QU'IL Y A PAS LE PARSING*/
	for (int i = 0; map[i][0] != END; i++) {
		for (int j = 0; map[i][j] != END; j++) {
			map[i][j] = mlx->map[i][j];
		}
	}
	/*****************************************/
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 1900, 950, "Cub3d");
	mlx_set_fps_goal(mlx->mlx, 60);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, close_window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, close_window, (void *)mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
}