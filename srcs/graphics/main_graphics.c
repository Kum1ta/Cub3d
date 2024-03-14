/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/14 14:01:06 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
}

void	put_fps(t_mlx *mlx)
{
	static long long	last_time = 0;
	static int			change = 0;
	long long			now;
	float				fps;
	static char			*tmp = NULL;

	now = get_now_time();
	fps = 1000000 / (now - last_time);
	last_time = now;
	if (change % 10 == 0)
	{
		if (tmp)
			free(tmp);
		tmp = ft_itoa(fps);
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 20, 15, 0xFFFF0000, tmp);
		change = 0;
	}
	else 
		mlx_string_put(mlx->mlx, mlx->win, WIDTH - 20, 15, 0xFFFF0000, tmp);
	change++;
}

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	larg_map(mlx);
	put_fps(mlx);
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

void	graphics_part(t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	init_mlx(mlx);
	mlx->map = map;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 1900, 950, "Cub3d");
	mlx_set_fps_goal(mlx->mlx, 60);
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, close_window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, close_window, (void *)mlx); // a adapter plus tard pour prendre tout le clavier
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
}