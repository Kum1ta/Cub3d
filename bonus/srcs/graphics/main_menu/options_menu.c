/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:58:46 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/12 20:09:57 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

typedef enum e_selected
{
	NOT_SELECTED,
	SELECTED,
}	t_selected;

void	add_case(t_mlx *mlx, int pos[4], char *str, int nbr_case, int list[2])
{
	static t_selected	selected[100];
	int	x;
	int	y;

	x = pos[0] - 1;
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
}

void	list_button_fps(t_mlx *mlx, int xy[2])
{
	add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Off", 0, (int [2]){0, 1});
	add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "On", 1, (int [2]){0, 1});
	// changer mlx->stg à partir des functions list_xx()
}

void	list_button_resolution(t_mlx *mlx, int xy[2])
{
	add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "800x600", 2, (int [2]){2, 6});
	add_case(mlx, (int [4]){xy[0] + 170, xy[1], xy[0] + 190, xy[1] + 20}, "1024x768", 3, (int [2]){2, 6});
	add_case(mlx, (int [4]){xy[0] + 350, xy[1], xy[0] + 370, xy[1] + 20}, "1280x800", 4, (int [2]){2, 6});
	add_case(mlx, (int [4]){xy[0] + 530, xy[1], xy[0] + 550, xy[1] + 20}, "1600x900", 5, (int [2]){2, 6});
	add_case(mlx, (int [4]){xy[0] + 710, xy[1], xy[0] + 730, xy[1] + 20}, "1920x1080", 6, (int [2]){2, 6});
	// changer mlx->stg à partir des functions list_xx()
}

void	list_button_quality(t_mlx *mlx, int xy[2])
{
	add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Very low", 7, (int [2]){7, 10});
	add_case(mlx, (int [4]){xy[0] + 180, xy[1], xy[0] + 200, xy[1] + 20}, "Low", 8, (int [2]){7, 10});
	add_case(mlx, (int [4]){xy[0] + 275, xy[1], xy[0] + 295, xy[1] + 20}, "Medium", 9, (int [2]){7, 10});
	add_case(mlx, (int [4]){xy[0] + 425, xy[1], xy[0] + 445, xy[1] + 20}, "High", 10, (int [2]){7, 10});
	// changer mlx->stg à partir des functions list_xx()
}

void	list_button_aa(t_mlx *mlx, int xy[2])
{
	add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "x1", 11, (int [2]){11, 14});
	add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "x2", 12, (int [2]){11, 14});
	add_case(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20}, "x4", 13, (int [2]){11, 14});
	add_case(mlx, (int [4]){xy[0] + 300, xy[1], xy[0] + 320, xy[1] + 20}, "x8", 14, (int [2]){11, 14});
	// changer mlx->stg à partir des functions list_xx()
}

void	list_button_mini_map(t_mlx *mlx, int xy[2])
{
	add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "Off", 15, (int [2]){15, 16});
	add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20}, "On", 16, (int [2]){15, 16});
	// changer mlx->stg à partir des functions list_xx()
}

void	options_menu(t_mlx *mlx, int need_free)
{
	static void	*square_img = NULL;
	static void	*bg = NULL;
	static int	diff = 50;
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40, 80, 0xFFFFFFFF, "Settings\b");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff, 0xFFFFFFFF, "Show fps : ");
	list_button_fps(mlx, (int [2]){270, 185 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 305 + diff, 0xFFFFFFFF, "Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 350 + diff, 0xFFFFFFFF, "Resolution         : ");
	list_button_resolution(mlx, (int [2]){430, 335 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 380 + diff, 0xFFFFFFFF, "Quality            : ");
	list_button_quality(mlx, (int [2]){430, 365 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 410 + diff, 0xFFFFFFFF, "Anti aliasing (SS) : ");
	list_button_aa(mlx, (int [2]){430, 395 + diff});
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 485 + diff, 0xFFFFFFFF, "Mini map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 530 + diff, 0xFFFFFFFF, "Show       : ");
	list_button_mini_map(mlx, (int [2]){300, 515 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 560 + diff, 0xFFFFFFFF, "Position X : ");
	mlx_string_put(mlx->mlx, mlx->win, 90, 590 + diff, 0xFFFFFFFF, "Position Y : ");

	add_button(mlx, (int [2]){mlx->stg->width - 100, mlx->stg->height - 30}, square_img, open_main_menu);
}

