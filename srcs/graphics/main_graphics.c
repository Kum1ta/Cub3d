/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 23:21:17 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

int	init(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->menu_map = malloc(sizeof(t_menu_map));
	if (!mlx->menu_map)
	{
		free(mlx);
		return (1);
	}
	mlx->mouse = malloc(sizeof(t_mouse));
	if (!mlx->mouse)
	{
		free(mlx->menu_map);
		free(mlx);
		return (1);
	}
	mlx->mouse->pressed_left = false;
	mlx->mouse->pressed_right = false;
	mlx->menu_map->x = 0;
	mlx->menu_map->y = 0;
	mlx->menu_map->size = 20;
	mlx->actuel_menu = GAME;
	mlx->keyboard = malloc(sizeof(t_keyboard));
	if (!mlx->keyboard)
	{
		free(mlx->menu_map);
		free(mlx->mouse);
		free(mlx);
		return (1);
	}
	mlx->keyboard->w = false;
	mlx->keyboard->a = false;
	mlx->keyboard->s = false;
	mlx->keyboard->d = false;
	mlx->keyboard->left = false;
	mlx->keyboard->right = false;
	mlx->keyboard->esc = false;
	return (0);
}

void	put_fps(t_mlx *mlx, int need_free)
{
	static long long	last_time = 0;
	static int			change = 0;
	long long			now;
	float				fps;
	static char			*tmp = NULL;

	if (need_free)
	{
		free(tmp);
		return ;
	}
	now = get_now_time();
	fps = 1000000 / (now - last_time);
	last_time = now;
	if (change % 10 == 0)
	{
		if (tmp)
			free(tmp);
		tmp = ft_itoa(fps);
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 25, 15, 0xFFFF0000, tmp);
		change = 0;
	}
	else 
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 25, 15, 0xFFFF0000, tmp);
	change++;
}


int	close_window(int event, void *mlx_ptr)
{
	t_mlx	*mlx;

	if	(event == 0)
	{
		mlx = (t_mlx *)mlx_ptr;
		destroy_textures(mlx);
		larg_map(mlx, 1);
		put_fps(mlx, 1);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free_all_graphics(mlx);
		exit(0);
	}
	return (0);
}

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;
	long long			now;

	now = get_now_time();
	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	if (mlx->mouse->pressed_left)
		mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->actuel_menu == MAP_LARG_MENU)
		larg_map(mlx, 0);
	else if (mlx->actuel_menu == GAME)
		raycasting(mlx);
	else
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50, HEIGHT / 2, 0xFFFF0000, "Error");
	put_fps(mlx, 0);
	if (now - get_now_time() < TIME_PER_FRAME_US * 1000)
		wait_us(TIME_PER_FRAME_US - (now - get_now_time()));
	return (0);
}

int	keyboard_status_down(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (key == 43 && mlx->actuel_menu == GAME)
		mlx->actuel_menu = MAP_LARG_MENU;
	else if (key == 43 && mlx->actuel_menu == MAP_LARG_MENU)
		mlx->actuel_menu = GAME;
	if (key == 26)
		mlx->keyboard->w = true;
	if (key == 4)
		mlx->keyboard->a = true;
	if (key == 22)
		mlx->keyboard->s = true;
	if (key == 7)
		mlx->keyboard->d = true;
	if (key == 80)
		mlx->keyboard->left = true;
	if (key == 79)
		mlx->keyboard->right = true;
	if (key == 41)
		mlx->keyboard->esc = true;
	return (0);
}

int	keyboard_status_up(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	if (key == 26)
		mlx->keyboard->w = false;
	if (key == 4)
		mlx->keyboard->a = false;
	if (key == 22)
		mlx->keyboard->s = false;
	if (key == 7)
		mlx->keyboard->d = false;
	if (key == 80)
		mlx->keyboard->left = false;
	if (key == 79)
		mlx->keyboard->right = false;
	if (key == 41)
		mlx->keyboard->esc = false;
	return (0);
}

void	graphics_part(t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	if (init(mlx))
	{
		ft_printf("Cube3d: Error init()\n");
		return ;
	}
	mlx->map = map;
	mlx->mlx = mlx_init();
	if (load_textures(mlx))
	{
		free(mlx);
		return ;
	}
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, close_window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, &keyboard_status_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, &keyboard_status_up, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEWHEEL, &mouse_whell, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN, &mouse_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP, &mouse_up, (void *)mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
}
