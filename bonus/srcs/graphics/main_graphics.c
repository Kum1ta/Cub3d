/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/04 15:26:28 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	inventory(t_mlx *mlx, void *img, int need_free);

int	window(int event, void *mlx_ptr)
{
	t_mlx	*mlx;

	if (event == 0)
	{
		mlx = (t_mlx *)mlx_ptr;
		destroy_textures(mlx);
		larg_map(mlx, 1);
		raycasting(mlx, 1);
		put_fps(mlx, 1);
		main_menu(mlx, 1);
		inventory(mlx, NULL, 1);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free_all_graphics(mlx);
		exit(0);
	}
	return (0);
}

void	graphics_part(t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	if (init(mlx, map))
	{
		ft_printf("Cube3d: Error init()\n");
		return ;
	}
	mlx->mlx = mlx_init();
	if (load_textures(mlx))
	{
		free(mlx);
		return ;
	}
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Kumilos - Cube3d");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, &keyboard_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, &keyboard_up, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEWHEEL, &mouse_whell, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN, &mouse_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP, &mouse_up, (void *)mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
}
