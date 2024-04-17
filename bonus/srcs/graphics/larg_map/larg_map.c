/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/17 17:07:56 by psalame          ###   ########.fr       */
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

char	*button_resume_lm(void *mlx_raw, int action)
{
	t_mlx	*mlx;

	if (action == 0 || action == 1)
		return ("Resume");
	mlx = mlx_raw;
	mouse_move(mlx);
	mlx->actuel_menu = GAME;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2, mlx->stg->height / 2);
	return (NULL);
}

void	change_config_file_lm(t_settings_window *stg)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;

	fd = open(".config", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	i = 0;
	while (i < 7)
	{
		if (i == 0)
		{
			tmp = ft_itoa(stg->show_fps);
			line = ft_strjoin("show_fps=", tmp);
		}
		else if (i == 1)
		{
			tmp = ft_itoa(stg->width);
			line = ft_strjoin("width=", tmp);
		}
		else if (i == 2)
		{
			tmp = ft_itoa(stg->height);
			line = ft_strjoin("height=", tmp);
		}
		else if (i == 3)
		{
			tmp = ft_itoa(stg->quality);
			line = ft_strjoin("quality=", tmp);
		}
		else if (i == 4)
		{
			tmp = ft_itoa(stg->anti_aliasing);
			line = ft_strjoin("antialiasing=", tmp);
		}
		else if (i == 5)
		{
			tmp = ft_itoa(stg->show_mini_map);
			line = ft_strjoin("show_minimap=", tmp);
		}
		else if (i == 6)
		{
			tmp = ft_itoa(stg->pos_mini_map);
			line = ft_strjoin("minimap_pos=", tmp);
		}
		free(tmp);
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(line);
		free(tmp);
		i++;
	}
	close(fd);
}

char	*button_main_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Back");
	((t_mlx *)mlx)->actuel_menu = MAP_LARG_MENU;
	((t_mlx *)mlx)->stg_win.width = ((t_mlx *)mlx)->stg->width;
	((t_mlx *)mlx)->stg_win.height = ((t_mlx *)mlx)->stg->height;
	((t_mlx *)mlx)->stg_win.show_mini_map = ((t_mlx *)mlx)->stg->show_minimap;
	((t_mlx *)mlx)->stg_win.pos_mini_map = ((t_mlx *)mlx)->stg->minimap_pos;
	change_config_file_lm(&((t_mlx *)mlx)->stg_win);
	((t_mlx *)mlx)->stg->show_fps = ((t_mlx *)mlx)->stg_win.show_fps;
	((t_mlx *)mlx)->stg->antialiasing = ((t_mlx *)mlx)->stg_win.anti_aliasing;
	((t_mlx *)mlx)->stg->quality = ((t_mlx *)mlx)->stg_win.quality;
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

/**************************************************************************/
int		add_case_lm(t_mlx *mlx, int pos[4], char *str, int nbr_case, int list[2]);
void	init_button_lm(t_mlx *mlx, t_selected (*selected)[22]);

void	list_button_fps_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Off", 0, (int [2]){0, 1}))
		mlx->stg_win.show_fps = 0;
	if (add_case_lm(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "On", 1, (int [2]){0, 1}))
		mlx->stg_win.show_fps = 1;
}

int	add_case_lm(t_mlx *mlx, int pos[4], char *str, int nbr_case, int list[2])
{
	static t_selected	selected[22];
	static int			init = 0;
	int					x;
	int					y;

	x = pos[0] - 1;
	if (!init)
	{
		init_button_lm(mlx, &selected);
		init = 1;
	}
	while (++x < pos[2])
	{
		y = pos[1] - 1;
		while (++y < pos[3])
		{
			if (x == pos[0] || x == pos[2] - 1 || y == pos[1] || y == pos[3] - 1)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFFFFFFFF);
			else if (mlx->mouse->x > pos[0] && mlx->mouse->x < pos[2] && mlx->mouse->y > pos[1] && mlx->mouse->y < pos[3] && selected[nbr_case] == NOT_SELECTED)
			{
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0x5F101010);
				if (mlx->mouse->pressed_left)
				{
					while (list[0] <= list[1])
						selected[list[0]++] = NOT_SELECTED;
					selected[nbr_case] = SELECTED;
					mlx->mouse->pressed_left = 0;
				}
			}
			else if (selected[nbr_case] == SELECTED)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0x5F0FF000);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, pos[0] + 30, pos[1] + 17, 0xFFFFFFFF, str);
	return (selected[nbr_case] == SELECTED);
}

void	init_button_lm(t_mlx *mlx, t_selected (*selected)[22])
{
	int	i;

	i = -1;
	if (mlx->stg->show_fps)
		(*selected)[1] = SELECTED;
	else
		(*selected)[0] = SELECTED;
	if (mlx->stg->quality == 5)
		(*selected)[7] = SELECTED;
	else if (mlx->stg->quality == 3)
		(*selected)[8] = SELECTED;
	else if (mlx->stg->quality == 2)
		(*selected)[9] = SELECTED;
	else if (mlx->stg->quality == 1)
		(*selected)[10] = SELECTED;
	if (mlx->stg->antialiasing == 1)
		(*selected)[11] = SELECTED;
	else if (mlx->stg->antialiasing == 2)
		(*selected)[12] = SELECTED;
	else if (mlx->stg->antialiasing == 4)
		(*selected)[13] = SELECTED;
	else if (mlx->stg->antialiasing == 8)
		(*selected)[14] = SELECTED;
}

void	list_button_quality_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Very low", 7, (int [2]){7, 10}))
		mlx->stg_win.quality = 5;
	if (add_case_lm(mlx, (int [4]){xy[0] + 180, xy[1], xy[0] + 200, xy[1] + 20}, "Low", 8, (int [2]){7, 10}))
		mlx->stg_win.quality = 3;
	if (add_case_lm(mlx, (int [4]){xy[0] + 275, xy[1], xy[0] + 295, xy[1] + 20}, "Medium", 9, (int [2]){7, 10}))
		mlx->stg_win.quality = 2;
	if (add_case_lm(mlx, (int [4]){xy[0] + 425, xy[1], xy[0] + 445, xy[1] + 20}, "High", 10, (int [2]){7, 10}))
		mlx->stg_win.quality = 1;
}

void	list_button_aa_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "x1", 11, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 1;
	if (add_case_lm(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "x2", 12, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 2;
	if (add_case_lm(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20}, "x4", 13, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 4;
	if (add_case_lm(mlx, (int [4]){xy[0] + 300, xy[1], xy[0] + 320, xy[1] + 20}, "x8", 14, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 8;
}

void	options_menu_lm(t_mlx *mlx, int need_free)
{
	static void		*bg_word = NULL;
	static t_img	bg;
	int				diff;

	if (need_free)
	{
		if (bg_word)
			mlx_destroy_image(mlx->mlx, bg_word);
		if (bg.img)
			mlx_destroy_image(mlx->mlx, bg.img);
		return ;
	}
	if (!bg_word)
	{
		bg_word = mlx_new_image(mlx->mlx, 200, 30);
		fill_image(mlx, bg_word, 0xEE009900, (int [2]){200, 30});
		bg.img = mlx_png_file_to_image(mlx->mlx, "textures/main_menu/bg_main_menu.png", &bg.width, &bg.height);
		if (!bg.img)
			return ;
	}
	diff = 50;
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg.img, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40, 80 + mlx->stg_win.diff, 0xFFFFFFFF, "Settings\b");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff, 0xFFFFFFFF, "Show fps : ");
	list_button_fps_lm(mlx, (int [2]){270, 185 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 265 + diff, 0xFFFFFFFF, "Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 310 + diff, 0xFFFFFFFF, "Quality");
	list_button_quality_lm(mlx, (int [2]){90, 325 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 380 + diff, 0xFFFFFFFF, "Anti aliasing (SS)");
	list_button_aa_lm(mlx, (int [2]){90, 395 + diff});
	add_button_lm(mlx, (int [2]){mlx->stg->width - 100, mlx->stg->height - 30}, bg_word, button_main_lm);
}

/**************************************************************************************************/

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
