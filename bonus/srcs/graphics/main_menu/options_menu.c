/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:58:46 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/08 19:35:10 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

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
		square_img = mlx_new_image(mlx->mlx, WIDTH - 140, 30);
		create_square(mlx, square_img, WIDTH - 140, 30);
		bg = mlx_png_file_to_image(mlx->mlx, "textures/main_menu/bg_main_menu.png", &tmp[0], &tmp[1]);

	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, bg, 0, 0);
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 64);
	mlx_string_put(mlx->mlx, mlx->win, 40, 80, 0xFFFFFFFF, "Settings\b");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff, 0xFFFFFFFF, "FOV      : ");
	mlx_string_put(mlx->mlx, mlx->win, 80, 230 + diff, 0xFFFFFFFF, "Show fps : ");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 305 + diff, 0xFFFFFFFF, "Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 350 + diff, 0xFFFFFFFF, "Resolution         : ");
	mlx_string_put(mlx->mlx, mlx->win, 90, 380 + diff, 0xFFFFFFFF, "Quality            : ");
	mlx_string_put(mlx->mlx, mlx->win, 90, 410 + diff, 0xFFFFFFFF, "Anti aliasing (SS) : ");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 485 + diff, 0xFFFFFFFF, "Mini map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 530 + diff, 0xFFFFFFFF, "Show       : ");
	mlx_string_put(mlx->mlx, mlx->win, 90, 560 + diff, 0xFFFFFFFF, "Position X : ");
	mlx_string_put(mlx->mlx, mlx->win, 90, 590 + diff, 0xFFFFFFFF, "Position Y : ");

	add_button(mlx, (int [2]){WIDTH - 100, HEIGHT - 30}, square_img, open_main_menu);
}

