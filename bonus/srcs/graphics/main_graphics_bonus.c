/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:18:39 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	window_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < mlx->stg->width && y < mlx->stg->height)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

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
		multiplayer_menu(mlx, 1);
		inventory(mlx, 1);
		options_menu(mlx, 1);
		dead_screen(mlx, 1);
		start_screen(mlx, 1);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		if (mlx->game_server.status == CONNECTED)
			close_server(&(mlx->game_server), DISCONNECTED);
		free_all_graphics(mlx);
		exit(0);
	}
	return (0);
}

void	mlx_init_event(t_mlx *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, &keyboard_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, &keyboard_up, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEWHEEL, &mouse_whell, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN, &mouse_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP, &mouse_up, (void *)mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
}

void	graphics_part(t_map *map, t_settings *settings)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
	{
		free_map(map);
		free(settings);
		return ;
	}
	if (init(mlx, map, settings))
	{
		ft_printf("Cube3d: Error init()\n");
		return ;
	}
	mlx->mlx = mlx_init();
	if (load_textures(mlx))
	{
		free_all_graphics(mlx);
		return ;
	}
	mlx->win = mlx_new_window(mlx->mlx, mlx->stg->width,
			mlx->stg->height, "Kumilos - Cube3d");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24.0f);
	mlx_init_event(mlx);
	mlx_loop(mlx->mlx);
}