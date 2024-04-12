/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/12 18:08:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	draw_square(t_mlx *mlx, int size, int color, int x, int y)
{
	int	i;
	int	j;

	i = x;
	while (i < x + size)
	{
		j = y;
		while (j < y + size)
		{
			if (i >= 0 && i < mlx->stg->width && j >= 0 && j < mlx->stg->height - 100)
				mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
			j++;
		}
		i++;
	}
}

void	update_pos(t_mlx *mlx)
{
	int	dx;
	int	dy;

	if (mlx->mouse->pressed_left)
	{
		dx = mlx->mouse->x - mlx->mouse->last_x;
		dy = mlx->mouse->y - mlx->mouse->last_y;
		mlx->menu_map->x += dx;
		mlx->menu_map->y += dy;
	}
	mlx->mouse->last_x = mlx->mouse->x;
	mlx->mouse->last_y = mlx->mouse->y;
}


void	fill_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < mlx->menu_map->size * mlx->map->height)
	{
		j = 0;
		while (j < mlx->menu_map->size * mlx->map->width)
		{
			if (mlx->map->blocks[i / mlx->menu_map->size][j / mlx->menu_map->size].type == WALL)
				draw_square(mlx, mlx->menu_map->size, 0xFF454545, j + mlx->menu_map->x - 3, i + mlx->menu_map->y - 3);
			else if (mlx->map->blocks[i / mlx->menu_map->size][j / mlx->menu_map->size].type == FLOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFFA1A1A1, j + mlx->menu_map->x, i + mlx->menu_map->y);
			else if (mlx->map->blocks[i / mlx->menu_map->size][j / mlx->menu_map->size].type == DOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFF222222, j + mlx->menu_map->x - 3, i + mlx->menu_map->y - 3);
			j += mlx->menu_map->size;
		}
		i += mlx->menu_map->size;
	}
}

void	fill_image(t_mlx *mlx, void *img, int color, int xy[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < xy[0])
	{
		j = 0;
		while (j < xy[1])
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			j++;
		}
		i++;
	}
}

void	put_player(t_mlx *mlx)
{
	int	i;
	int	k;

	i = mlx->menu_map->size * mlx->map->playerPos.y;
	k = mlx->menu_map->size * mlx->map->playerPos.x;
	draw_square(mlx, mlx->menu_map->size / 2, 0xFF0000FF,
		k + mlx->menu_map->x - mlx->menu_map->size / 4,
		i + mlx->menu_map->y - mlx->menu_map->size / 4);
}

void	add_button_lm(t_mlx *mlx, int xy[2], void *img, char *(*f)(void *, int))
{
	if (mlx->mouse->x > xy[0] - 10 && mlx->mouse->x < xy[0] + 130 && mlx->mouse->y > xy[1] - 30 && mlx->mouse->y < xy[1] + 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, xy[0] - 10, xy[1] - 22);
		if (mlx->mouse->pressed_left)
		{
			f((void *)mlx, 1);
			mlx->menu_button_focus = (intptr_t) f((void *)mlx, 2);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, xy[0], xy[1], 0xFFFFFFFF, f((void *)mlx, 0));
}

char	*button_resume_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Resume");
	mouse_move((t_mlx *)mlx);
	((t_mlx *)mlx)->actuel_menu = GAME;
	return (NULL);
}

char	*button_main_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Back");
	((t_mlx *)mlx)->actuel_menu = MAP_LARG_MENU;
	return (NULL);
}

char	*button_option_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Options");
	((t_mlx *)mlx)->actuel_menu = OPTIONS_LM;
	return (NULL);
}

char	*main_menu_lm(void *mlxRaw, int action)
{
	t_mlx *mlx;

	if (action == 0)
		return ("Quit");
	mlx = mlxRaw;
	mlx->actuel_menu = MAIN_MENU;
	if (mlx->game_server.status == CONNECTED)
		close_server(&mlx->game_server, DISCONNECTED);
	return (NULL);
}

void	options_menu_lm(t_mlx *mlx, int need_free)
{
	static void	*bg_word = NULL;

	if (need_free)
	{
		if (bg_word)
			mlx_destroy_image(mlx->mlx, bg_word);
		return ;
	}
	if (!bg_word)
	{
		bg_word = mlx_new_image(mlx->mlx, 200, 30);
		fill_image(mlx, bg_word, 0xEE009900, (int [2]){200, 30});
	}
	mlx_string_put(mlx->mlx, mlx->win, 40, 80, 0xFFFFFFFF, "Tqt c'est les settings ici");
	add_button_lm(mlx, (int [2]){mlx->stg->width - 100, mlx->stg->height - 30}, bg_word, button_main_lm);
}

void	down_bar(t_mlx *mlx, int need_free)
{
	static void	*img = NULL;
	static void	*bg_word = NULL;

	if (need_free)
	{
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		if (bg_word)
			mlx_destroy_image(mlx->mlx, bg_word);
		return ;
	}
	if (!img)
	{
		img = mlx_new_image(mlx->mlx, mlx->stg->width, 100);
		fill_image(mlx, img, 0xFF212121, (int [2]){mlx->stg->width, 100});
	}
	if (!bg_word)
	{
		bg_word = mlx_new_image(mlx->mlx, 140, 30);
		fill_image(mlx, bg_word, 0xEE009900, (int [2]){140, 30});
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, mlx->stg->height - 100);
	add_button_lm(mlx, (int [2]){50, mlx->stg->height - 40}, bg_word, button_resume_lm);
	add_button_lm(mlx, (int [2]){200, mlx->stg->height - 40}, bg_word, button_option_lm);
	add_button_lm(mlx, (int [2]){360, mlx->stg->height - 40}, bg_word, main_menu_lm);
}


void	larg_map(t_mlx *mlx, int need_free)
{
	if (need_free)
	{
		down_bar(mlx, 1);
		options_menu_lm(mlx, 1);
		return ;
	}
	update_pos(mlx);
	fill_map(mlx);
	put_player(mlx);
	down_bar(mlx, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 14);
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 275, mlx->stg->height - 60, 0xFFFFFFFF,
		"'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width - 210, mlx->stg->height - 40, 0xFFFFFFFF,
		"'r' to reset the map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	
}
