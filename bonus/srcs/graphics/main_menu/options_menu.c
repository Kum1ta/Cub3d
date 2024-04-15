/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:58:46 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 23:15:10 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	init_button(t_mlx *mlx, t_selected (*selected)[22])
{
	int	i;

	i = -1;
	if (mlx->stg->show_fps)
		(*selected)[1] = SELECTED;
	else
		(*selected)[0] = SELECTED;
	if (mlx->stg->width == 800 && mlx->stg->height == 600)
		(*selected)[2] = SELECTED;
	else if (mlx->stg->width == 1024 && mlx->stg->height == 768)
		(*selected)[3] = SELECTED;
	else if (mlx->stg->width == 1280 && mlx->stg->height == 800)
		(*selected)[4] = SELECTED;
	else if (mlx->stg->width == 1600 && mlx->stg->height == 900)
		(*selected)[5] = SELECTED;
	else if (mlx->stg->width == 1920 && mlx->stg->height == 1080)
		(*selected)[6] = SELECTED;
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
	if (mlx->stg->show_minimap)
		(*selected)[16] = SELECTED;
	else
		(*selected)[15] = SELECTED;
	if (mlx->stg->minimap_pos == 0)
		(*selected)[17] = SELECTED;
	else if (mlx->stg->minimap_pos == 1)
		(*selected)[18] = SELECTED;
	else if (mlx->stg->minimap_pos == 2)
		(*selected)[19] = SELECTED;
}

int	add_case(t_mlx *mlx, int pos[4], char *str, int nbr_case, int list[2])
{
	static t_selected	selected[22];
	static int			init = 0;
	int					x;
	int					y;

	x = pos[0] - 1;
	if (!init)
	{
		init_button(mlx, &selected);
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

void	list_button_fps(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Off", 0, (int [2]){0, 1}))
		mlx->stg_win.show_fps = 0;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "On", 1, (int [2]){0, 1}))
		mlx->stg_win.show_fps = 1;
}

void	list_button_resolution(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "800x600", 2, (int [2]){2, 6}))
	{
		mlx->stg_win.width = 800;
		mlx->stg_win.height = 600;
	}
	if (add_case(mlx, (int [4]){xy[0] + 170, xy[1], xy[0] + 190, xy[1] + 20}, "1024x768", 3, (int [2]){2, 6}))
	{
		mlx->stg_win.width = 1024;
		mlx->stg_win.height = 768;
	}
	if (add_case(mlx, (int [4]){xy[0] + 350, xy[1], xy[0] + 370, xy[1] + 20}, "1280x800", 4, (int [2]){2, 6}))
	{
		mlx->stg_win.width = 1280;
		mlx->stg_win.height = 800;
	}
	if (add_case(mlx, (int [4]){xy[0] + 530, xy[1], xy[0] + 550, xy[1] + 20}, "1600x900", 5, (int [2]){2, 6}))
	{
		mlx->stg_win.width = 1600;
		mlx->stg_win.height = 900;
	}
	if (add_case(mlx, (int [4]){xy[0], xy[1] + 30, xy[0] + 20, xy[1] + 50}, "1920x1080", 6, (int [2]){2, 6}))
	{
		mlx->stg_win.width = 1920;
		mlx->stg_win.height = 1080;
	}
}

void	list_button_quality(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Very low", 7, (int [2]){7, 10}))
		mlx->stg_win.quality = 5;
	if (add_case(mlx, (int [4]){xy[0] + 180, xy[1], xy[0] + 200, xy[1] + 20}, "Low", 8, (int [2]){7, 10}))
		mlx->stg_win.quality = 3;
	if (add_case(mlx, (int [4]){xy[0] + 275, xy[1], xy[0] + 295, xy[1] + 20}, "Medium", 9, (int [2]){7, 10}))
		mlx->stg_win.quality = 2;
	if (add_case(mlx, (int [4]){xy[0] + 425, xy[1], xy[0] + 445, xy[1] + 20}, "High", 10, (int [2]){7, 10}))
		mlx->stg_win.quality = 1;
}

void	list_button_aa(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "x1", 11, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 1;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "x2", 12, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 2;
	if (add_case(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20}, "x4", 13, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 4;
	if (add_case(mlx, (int [4]){xy[0] + 300, xy[1], xy[0] + 320, xy[1] + 20}, "x8", 14, (int [2]){11, 14}))
		mlx->stg_win.anti_aliasing = 8;
}

void	list_button_mini_map(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Off", 15, (int [2]){15, 16}))
		mlx->stg_win.show_mini_map = 0;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "On", 16, (int [2]){15, 16}))
		mlx->stg_win.show_mini_map = 1;
}

void	list_position_mini_map(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "top-left", 17, (int [2]){17, 19}))
		mlx->stg_win.pos_mini_map = 0;
	if (add_case(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20}, "top-right", 18, (int [2]){17, 19}))
		mlx->stg_win.pos_mini_map = 1;
	if (add_case(mlx, (int [4]){xy[0] + 400, xy[1], xy[0] + 420, xy[1] + 20}, "bottom-left", 19, (int [2]){17, 19}))
		mlx->stg_win.pos_mini_map = 2;
}

void	change_config_file(t_settings_window *stg)
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

int	main(int ac, char **av);

char	*back_main_menu(void *mlx, int action)
{
	((t_mlx *)mlx)->mouse->pressed_left = 0;
	if (action == 0)
		return ("Apply");
	change_config_file(&(((t_mlx *)mlx)->stg_win));
	((t_mlx *)mlx)->actuel_menu = WAIT_QUIT;
	return (NULL);
}

void	options_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static void	*bg = NULL;
	int			diff;
	int			tmp[2];

	if (need_free)
	{
		if (square_img)
			mlx_destroy_image(mlx->mlx, square_img);
		if (bg)
			mlx_destroy_image(mlx->mlx, bg);
		return ;
	}
	if (!square_img)
	{
		square_img = mlx_new_image(mlx->mlx, mlx->stg->width - 140, 30);
		create_square(mlx, square_img, mlx->stg->width - 140, 30);
		bg = mlx_png_file_to_image(mlx->mlx, "textures/main_menu/bg_main_menu.png", &tmp[0], &tmp[1]);
	}
	diff = 50 + mlx->stg_win.diff;
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40, 80 + mlx->stg_win.diff, 0xFFFFFFFF, "Settings\b");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff, 0xFFFFFFFF, "Show fps : ");
	list_button_fps(mlx, (int [2]){270, 185 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 265 + diff, 0xFFFFFFFF, "Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 310 + diff, 0xFFFFFFFF, "Resolution");
	list_button_resolution(mlx, (int [2]){90, 330 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 420 + diff, 0xFFFFFFFF, "Quality");
	list_button_quality(mlx, (int [2]){90, 440 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 500 + diff, 0xFFFFFFFF, "Anti aliasing (SS)");
	list_button_aa(mlx, (int [2]){90, 520 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 610 + diff, 0xFFFFFFFF, "Mini map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 660 + diff, 0xFFFFFFFF, "Show       : ");
	list_button_mini_map(mlx, (int [2]){300, 645 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 690 + diff, 0xFFFFFFFF, "Position");
	list_position_mini_map(mlx, (int [2]){93, 705 + diff});
	add_button(mlx, (int [2]){mlx->stg->width - 100, mlx->stg->height - 30}, square_img, back_main_menu);
}

